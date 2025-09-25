#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> matrix;
map<char, pair<int,int>> pos;

// Tạo ma trận Playfair từ key
void generateMatrix(const string &key) {
    matrix.assign(5, vector<char>(5));
    pos.clear(); // Xóa dữ liệu cũ

    string s = "";
    vector<bool> used(26,false);

    for(char c:key){
        if(!isalpha(c)) continue;
        c = toupper(c);
        if(c=='J') c='I';
        if(!used[c-'A']){
            used[c-'A']=true;
            s+=c;
        }
    }

    for(char c='A'; c<='Z'; c++){
        if(c=='J') continue;
        if(!used[c-'A']){
            used[c-'A']=true;
            s+=c;
        }
    }

    int k=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            matrix[i][j]=s[k];
            pos[s[k]]={i,j};
            k++;
        }
    }
}

// In ma trận Playfair (debug)
void printMatrix() {
    cout << "Ma tran Playfair:\n";
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++) cout << matrix[i][j] << " ";
        cout << endl;
    }
}

// Chuẩn hóa văn bản
string prepareText(string text) {
    string s="";
    for(char c:text){
        if(isalpha(c)){
            c = toupper(c);
            if(c=='J') c='I';
            s+=c;
        }
    }
    return s;
}

// Mã hóa cặp ký tự
string encryptPair(char a, char b) {
    int r1=pos[a].first,c1=pos[a].second;
    int r2=pos[b].first,c2=pos[b].second;
    if(r1==r2) return string(1,matrix[r1][(c1+1)%5]) + matrix[r2][(c2+1)%5];
    else if(c1==c2) return string(1,matrix[(r1+1)%5][c1]) + matrix[(r2+1)%5][c2];
    else return string(1,matrix[r1][c2]) + matrix[r2][c1];
}

// Giải mã cặp ký tự
string decryptPair(char a, char b) {
    int r1=pos[a].first,c1=pos[a].second;
    int r2=pos[b].first,c2=pos[b].second;
    if(r1==r2) return string(1,matrix[r1][(c1+4)%5]) + matrix[r2][(c2+4)%5];
    else if(c1==c2) return string(1,matrix[(r1+4)%5][c1]) + matrix[(r2+4)%5][c2];
    else return string(1,matrix[r1][c2]) + matrix[r2][c1];
}

// Mã hóa Playfair
string playfairEncrypt(string text, string key) {
    generateMatrix(key);
    text = prepareText(text);
    string res="";
    for(int i=0;i<text.size();){
        char a=text[i];
        char b = (i+1 < text.size() ? text[i+1] : 'X');
        if(a==b){ b='X'; i++; }
        else i+=2;
        res+=encryptPair(a,b);
    }
    return res;
}

// Giải mã Playfair
string playfairDecrypt(string text, string key) {
    generateMatrix(key);
    text = prepareText(text);
    string res="";
    for(int i=0;i<text.size();i+=2){
        char a=text[i];
        char b = (i+1 < text.size() ? text[i+1] : 'X');
        res+=decryptPair(a,b);
    }
    return res;
}

int main() {
    string plain, cipher, key;
    cout << "=== Ma hoa Playfair ===\n";
    cout << "Nhap chuoi can ma hoa: ";
    getline(cin, plain);
    cout << "Nhap khoa: ";
    getline(cin, key);

    string mahoa = playfairEncrypt(plain, key);
    cout << "Chuoi ma hoa: " << mahoa << endl;

    printMatrix(); // In ma trận để debug

    cout << "\nNhap chuoi da ma hoa de giai ma: ";
    getline(cin, cipher);
    cout << "Chuoi giai ma: " << playfairDecrypt(cipher, key) << endl;

    return 0;
}
