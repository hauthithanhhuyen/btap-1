#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
using namespace std;
// Helpers
string sanitize(const string &s) {
    string r;
    for(char c: s) if(isalpha((unsigned char)c)) r += toupper(c);
    return r;
}
int mod26(int x){ x%=26; if(x<0) x+=26; return x; }
int egcd(int a,int b,int &x,int &y){
    if(b==0){ x= (a>=0?1:-1); y=0; return abs(a); }
    int x1,y1; int g=egcd(b,a%b,x1,y1);
    x=y1; y=x1 - (a/b)*y1; return g;
}
int modinv(int a, int m){
    int x,y; if(egcd(a,m,x,y)!=1) return -1;
    int inv = x % m; if(inv<0) inv+=m; return inv;
}

// 1) Caesar
string caesar_encrypt(const string &pt, int k){
    string s = sanitize(pt); string out;
    for(char c: s) out += char('A' + (c - 'A' + k)%26);
    return out;
}
string caesar_decrypt(const string &ct, int k){
    return caesar_encrypt(ct, 26 - (k%26));
}

// 2) Affine
string affine_encrypt(const string &pt, int a, int b){
    string s = sanitize(pt); string out;
    for(char c: s) out += char('A' + mod26(a*(c-'A') + b));
    return out;
}
string affine_decrypt(const string &ct, int a, int b){
    int a_inv = modinv(a,26); if(a_inv==-1) return "";
    string out; for(char c: sanitize(ct)) out += char('A' + mod26(a_inv*(c-'A' - b)));
    return out;
}

// 3) Columnar transposition (key: word -> numeric order)
vector<int> key_order(const string &key){
    int n=key.size();
    vector<pair<char,int>> v;
    for(int i=0;i<n;i++) v.push_back({key[i],i});
    sort(v.begin(), v.end(), [](auto &a, auto &b){
        if(a.first!=b.first) return a.first < b.first; return a.second < b.second;
    });
    vector<int> order(n);
    for(int i=0;i<n;i++) order[v[i].second]=i;
    return order;
}
string columnar_encrypt(const string &pt, const string &key_in){
    string key = key_in;
    if(key.empty()) key = "KEY"; // avoid zero columns
    string s = sanitize(pt); int cols = key.size();
    int rows = (s.size() + cols -1)/cols;
    while((int)s.size() < rows*cols) s += 'X';
    vector<int> order = key_order(key);
    string out;
    for(int colRank=0; colRank<cols; ++colRank){
        for(int c=0;c<cols;c++) if(order[c]==colRank){
            for(int r=0;r<rows;r++) out += s[r*cols + c];
            break;
        }
    }
    return out;
}
string columnar_decrypt(const string &ct, const string &key_in){
    string key = key_in;
    if(key.empty()) key = "KEY"; // avoid zero columns
    string s = sanitize(ct); int cols = key.size();
    int rows = (s.size() + cols -1)/cols;
    vector<int> order = key_order(key);
    vector<string> col(cols, string(rows,' '));
    int pos=0;
    for(int colRank=0; colRank<cols; ++colRank){
        for(int c=0;c<cols;c++) if(order[c]==colRank){
            for(int r=0;r<rows;r++) if(pos < (int)s.size()) col[c][r] = s[pos++]; else col[c][r] = 'X';
            break;
        }
    }
    string out;
    for(int r=0;r<rows;r++) for(int c=0;c<cols;c++) out += col[c][r];
    return out;
}

// 4) Vigenere
string vigenere_encrypt(const string &pt, const string &key){
    string s = sanitize(pt), k = sanitize(key);
    string out; int m = k.size();
    if(m==0) return s;
    for(int i=0;i<(int)s.size();i++){
        int shift = k[i % m] - 'A';
        out += char('A' + (s[i]-'A' + shift)%26);
    }
    return out;
}
string vigenere_decrypt(const string &ct, const string &key){
    string s = sanitize(ct), k = sanitize(key); string out; int m=k.size(); if(m==0) return s;
    for(int i=0;i<(int)s.size();i++){
        int shift = k[i % m] - 'A';
        out += char('A' + mod26(s[i]-'A' - shift));
    }
    return out;
}

// 5) Playfair
struct PF {
    char table[5][5];
    map<char,pair<int,int>> pos;
    PF(const string &key){
        string k = sanitize(key);
        vector<bool> used(26,false);
        used['J'-'A'] = true; // merge I/J
        string seq;
        for(char c: k){
            char cc = (c=='J'?'I':c);
            if(!used[cc-'A']){ used[cc-'A']=true; seq+=cc; }
        }
        for(char c='A'; c<='Z'; c++){
            if(!used[c-'A']){ seq+=c; }
        }
        int p=0;
        for(int r=0;r<5;r++) for(int c=0;c<5;c++){
            table[r][c] = seq[p++];
            pos[table[r][c]] = {r,c};
        }
        // ensure 'J' maps to same position as 'I' so incoming 'J' won't break decrypt
        if(pos.find('I') != pos.end()){
            pos['J'] = pos['I'];
        }
    }
    string prepare(const string &pt){
        string s = sanitize(pt);
        for(char &c: s) if(c=='J') c='I';
        string out;
        for(size_t i=0;i<s.size();){
            char a = s[i];
            char b = (i+1 < s.size()? s[i+1] : 'X');
            if(a==b){ out += a; out += 'X'; i++; }
            else{ out += a; out += b; i+=2; }
        }
        if(out.size()%2) out += 'X';
        return out;
    }
    string encrypt(const string &pt){
        string s = prepare(pt), out;
        for(size_t i=0;i<s.size(); i+=2){
            // use 'I' for any 'J' (should not appear after prepare, but be safe)
            char ca = (s[i]=='J' ? 'I' : s[i]);
            char cb = (s[i+1]=='J' ? 'I' : s[i+1]);
            auto pa = pos.at(ca);
            auto pb = pos.at(cb);
            if(pa.first == pb.first){
                out += table[pa.first][(pa.second+1)%5];
                out += table[pb.first][(pb.second+1)%5];
            } else if(pa.second == pb.second){
                out += table[(pa.first+1)%5][pa.second];
                out += table[(pb.first+1)%5][pb.second];
            } else {
                out += table[pa.first][pb.second];
                out += table[pb.first][pa.second];
            }
        }
        return out;
    }
    string decrypt(const string &ct){
        string s = sanitize(ct), out;
        for(size_t i=0;i<s.size(); i+=2){
            char ca = (s[i]=='J' ? 'I' : s[i]);
            char cb = (s[i+1]=='J' ? 'I' : s[i+1]);
            auto pa = pos.at(ca);
            auto pb = pos.at(cb);
            if(pa.first == pb.first){
                out += table[pa.first][(pa.second+4)%5];
                out += table[pb.first][(pb.second+4)%5];
            } else if(pa.second == pb.second){
                out += table[(pa.first+4)%5][pa.second];
                out += table[(pb.first+4)%5][pb.second];
            } else {
                out += table[pa.first][pb.second];
                out += table[pb.first][pa.second];
            }
        }
        return out;
    }
};

// Demo CLI (rất đơn giản)
int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto usage = [&](){
        cerr << "Usage:\n";
        cerr << "  classical_ciphers <method> <enc|dec> <key> <text...>\n";
        cerr << "Methods and key format:\n";
        cerr << "  caesar <k>                 (k integer)\n";
        cerr << "  affine <a,b>               (a,b integers, a invertible mod26, e.g. 5,8)\n";
        cerr << "  columnar <keyword>         (keyword string)\n";
        cerr << "  vigenere <keyword>         (keyword string)\n";
        cerr << "  playfair <keyword>         (keyword string, J merged with I)\n";
        cerr << "Examples:\n";
        cerr << "  classical_ciphers caesar enc 3 \"ATTACK AT DAWN\"\n";
        cerr << "  classical_ciphers affine dec \"5,8\" \"FKRRQ\"\n";
        cerr << "  classical_ciphers playfair enc PLAYFAIR \"HIDE THE GOLD\"\n";
    };

    if(argc < 2){
        usage();
        return 0;
    }

    string method = (argc>1 ? string(argv[1]) : "");
    string mode = (argc>2 ? string(argv[2]) : "enc"); // default encrypt
    string key = (argc>3 ? string(argv[3]) : "");
    // collect remaining args as text; if none, read from stdin
    string text;
    if(argc > 4){
        for(int i=4;i<argc;i++){
            if(i>4) text += " ";
            text += argv[i];
        }
    } else {
        // try read rest of stdin if piped / provided
        std::string line;
        bool any=false;
        while(std::getline(cin, line)){
            if(any) text += "\n";
            text += line; any=true;
        }
    }

    if(text.empty()){
        cerr << "No text provided.\n";
        usage();
        return 1;
    }

    // compute result
    string result;
    try {
        if(method == "caesar"){
            int k = 0;
            if(key.empty()){ cerr << "Missing key for caesar\n"; return 1; }
            k = stoi(key);
            if(mode == "enc") result = caesar_encrypt(text, k);
            else result = caesar_decrypt(text, k);
        } else if(method == "affine"){
            if(key.empty()){ cerr << "Missing key for affine (a,b)\n"; return 1; }
            // accept "a,b" or "a b"
            int a=0,b=0;
            string k = key;
            size_t pos = k.find(',');
            if(pos != string::npos){
                a = stoi(k.substr(0,pos));
                b = stoi(k.substr(pos+1));
            } else {
                // try split by space (unlikely since single argv) or parse whole as single int -> treat b=0
                size_t sp = k.find_first_of(" ");
                if(sp != string::npos){
                    a = stoi(k.substr(0,sp));
                    b = stoi(k.substr(sp+1));
                } else {
                    // if only one number provided, treat as a, b=0
                    a = stoi(k); b = 0;
                }
            }
            if(mode=="enc") result = affine_encrypt(text,a,b);
            else result = affine_decrypt(text,a,b);
        } else if(method == "columnar"){
            string kw = key.empty() ? "KEY" : key;
            if(mode=="enc") result = columnar_encrypt(text, kw);
            else result = columnar_decrypt(text, kw);
        } else if(method == "vigenere"){
            string kw = key;
            if(mode=="enc") result = vigenere_encrypt(text, kw);
            else result = vigenere_decrypt(text, kw);
        } else if(method == "playfair"){
            string kw = key.empty() ? "PLAYFAIR" : key;
            PF pf(kw);
            if(mode=="enc") result = pf.encrypt(text);
            else result = pf.decrypt(text);
        } else {
            cerr << "Unknown method: " << method << "\n";
            usage();
            return 1;
        }
    } catch(const exception &e){
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    cout << result << "\n";
    return 0;
}