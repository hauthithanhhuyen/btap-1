#include <bits/stdc++.h>
using namespace std;

// Mã hóa Vigenere
string vigenereEncrypt(const string &text, const string &key) {
    string res = "";
    int n = key.size(), j = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c)?'A':'a';
            int k = toupper(key[j % n]) - 'A';
            res += char((c - base + k) % 26 + base);
            j++;
        } else res += c;
    }
    return res;
}

// Giải mã Vigenere
string vigenereDecrypt(const string &text, const string &key) {
    string res = "";
    int n = key.size(), j = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c)?'A':'a';
            int k = toupper(key[j % n]) - 'A';
            res += char((c - base - k + 26) % 26 + base);
            j++;
        } else res += c;
    }
    return res;
}

int main() {
    string plain, cipher, key;
    cout << "=== Ma hoa Vigenere ===\n";
    cout << "Nhap chuoi can ma hoa: ";
    getline(cin, plain);
    cout << "Nhap khoa (chuoi): ";
    getline(cin, key);

    string mahoa = vigenereEncrypt(plain, key);
    cout << "Chuoi ma hoa: " << mahoa << endl;

    cout << "\nNhap chuoi da ma hoa de giai ma: ";
    getline(cin, cipher);
    cout << "Chuoi giai ma: " << vigenereDecrypt(cipher, key) << endl;

    return 0;
}
