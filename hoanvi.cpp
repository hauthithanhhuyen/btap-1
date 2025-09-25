#include <bits/stdc++.h>
using namespace std;

// Mã hóa Hoán vị
string encryptPermutation(const string &text, const vector<int> &key) {
    string res = "";
    int n = key.size();
    for (int i = 0; i < (int)text.size(); i += n) {
        string block = text.substr(i, n);
        while (block.size() < n) block += 'X'; // padding
        string encBlock(n, ' ');
        for (int j = 0; j < n; j++) {
            encBlock[j] = block[key[j]];
        }
        res += encBlock;
    }
    return res;
}

// Giải mã Hoán vị
string decryptPermutation(const string &text, const vector<int> &key) {
    string res = "";
    int n = key.size();
    vector<int> invKey(n);
    for (int i = 0; i < n; i++) invKey[key[i]] = i;

    for (int i = 0; i < (int)text.size(); i += n) {
        string block = text.substr(i, n);
        string decBlock(n, ' ');
        for (int j = 0; j < n; j++) {
            decBlock[invKey[j]] = block[j];
        }
        res += decBlock;
    }
    return res;
}

int main() {
    string plain, cipher;
    int n;

    cout << "=== Ma hoa Hoan Vi ===\n";
    cout << "Nhap chuoi can ma hoa: ";
    getline(cin, plain);
    cout << "Nhap kich thuoc khoa n: ";
    cin >> n;
    vector<int> key(n);
    cout << "Nhap khoa hoan vi: ";
    for (int i = 0; i < n; i++) cin >> key[i];
    cin.ignore();

    string mahoa = encryptPermutation(plain, key);
    cout << "Chuoi ma hoa: " << mahoa << endl;

    cout << "\nNhap chuoi da ma hoa de giai ma: ";
    getline(cin, cipher);
    cout << "Chuoi giai ma: " << decryptPermutation(cipher, key) << endl;

    return 0;
}
