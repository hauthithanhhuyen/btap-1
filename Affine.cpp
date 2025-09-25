#include <bits/stdc++.h>
using namespace std;

// Tìm nghịch đảo modulo
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) 
        if ((a * x) % m == 1) return x;
    return -1;
}

// Mã hóa Affine
string maHoaAffine(string text, int a, int b) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            res += char(((a * (c - base) + b) % 26) + base);
        } else res += c;
    }
    return res;
}

// Giải mã Affine
string giaiMaAffine(string text, int a, int b) {
    string res = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) return "Khoa a khong hop le (khong co nghich dao modulo 26)!";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            res += char((a_inv * ((c - base) - b + 26)) % 26 + base);
        } else res += c;
    }
    return res;
}

int main() {
    string plain, cipher;
    int a, b;

    cout << "=== Ma hoa Affine ===\n";
    cout << "Nhap chuoi can ma hoa: ";
    getline(cin, plain);
    cout << "Nhap khoa a, b: ";
    cin >> a >> b;
    cin.ignore();

    // Mã hóa
    string mahoa = maHoaAffine(plain, a, b);
    cout << "Chuoi ma hoa: " << mahoa << endl;

    // Giải mã (người dùng tự nhập chuỗi mã hóa)
    cout << "\nNhap chuoi da ma hoa de giai ma: ";
    getline(cin, cipher);

    string giaima = giaiMaAffine(cipher, a, b);
    cout << "Chuoi giai ma: " << giaima << endl;

    return 0;
}
