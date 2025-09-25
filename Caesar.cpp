#include <bits/stdc++.h>
using namespace std;

// Mã hóa Caesar
string caesarEncrypt(const string &text, int key) {
    string res="";
    key = (key % 26 + 26) % 26; // chuẩn hóa key
    for(char c:text){
        if(isalpha(c)){
            char base = isupper(c)?'A':'a';
            res += char((c - base + key) % 26 + base);
        } else res += c;
    }
    return res;
}

// Giải mã Caesar
string caesarDecrypt(const string &text, int key) {
    string res="";
    key = (key % 26 + 26) % 26;
    for(char c:text){
        if(isalpha(c)){
            char base = isupper(c)?'A':'a';
            res += char((c - base - key + 26) % 26 + base);
        } else res += c;
    }
    return res;
}

int main() {
    string plain, cipher;
    int k;

    cout << "=== Ma hoa Caesar ===\n";
    cout << "Nhap chuoi can ma hoa: ";
    getline(cin, plain);
    cout << "Nhap khoa k: ";
    cin >> k;
    cin.ignore();

    string mahoa = caesarEncrypt(plain, k);
    cout << "Chuoi ma hoa: " << mahoa << endl;

    cout << "\nNhap chuoi da ma hoa de giai ma: ";
    getline(cin, cipher);
    cout << "Chuoi giai ma: " << caesarDecrypt(cipher, k) << endl;

    return 0;
}
