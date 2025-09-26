# btap-1
k225480106027 hầu thanh huyền
# TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
Caesar
Affine
Hoán vị
Vigenère
Playfair
# Với mỗi phương pháp, hãy tìm hiểu:
Tên gọi
Thuật toán mã hoá, thuật toán giải mã
Không gian khóa
Cách phá mã (mà không cần khoá)
Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript</p>

### Encrypt (mã hoá): chuyển dữ liệu rõ (plaintext) thành dữ liệu đã được mã (ciphertext) bằng một thuật toán và (thường) một khóa, để che giấu nội dung.
### Decrypt (giải mã): đảo lại quá trình mã hoá, dùng thuật toán và khóa thích hợp để lấy lại plaintext từ ciphertext.

## Bài Làm

#  1. Mã hóa Affine (Affine Cipher)
## Cách làm Mỗi ký tự được biến đổi bằng công thức tuyến tính.
## Công thức mã hóa: C = (a*P + b) mod 26
## Công thức giải mã: P = a⁻¹ * (C - b) mod 26
## Không gian khóa: phi(26)26 = 1226 = 312 (a có 12 lựa chọn, b 0..25)
## Cách phá: thử tất cả cặp (a,b) (brute-force 312); phân tích tần suất.
# Kết Quả Hiển Thị  
 ### Sử dụng thuật toán
 <img width="1167" height="707" alt="{16D1F83C-4904-4745-AE32-D8817067C35B}" src="https://github.com/user-attachments/assets/e6479f1e-9937-4908-a712-d835c6de8eac" />
### Đã giải mã 
<img width="802" height="790" alt="{5E55F458-4F97-40D2-9D7A-CCF37363AC01}" src="https://github.com/user-attachments/assets/e3a510b2-aecc-481a-a728-cb7c07b52067" /></p>
## Đã mã hóa và giải mã qua C++
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

<img width="1153" height="420" alt="{6E9C75D9-AB64-4742-8916-8439E7E9892E}" src="https://github.com/user-attachments/assets/f1f64710-15d7-44d3-aabb-07856ce491f7" /></p>

# 2. Mã hóa Caesar (Caesar Cipher)

## Cách làm:

## Dịch chuyển mỗi ký tự trong bản rõ một số vị trí trong bảng chữ cái.

## Công thức mã hóa: C = (P + k) mod 26

## Công thức giải mã: P = (C - k + 26) mod 26

## Không gian khóa: 25 (k=1..25)

## Cách phá: brute-force thử 25 shift; phân tích tần suất để chọn dịch phù hợp.</p>

Trong đó:

- P: ký tự bản rõ (Plaintext)

- C: ký tự bản mã (Ciphertext)

- k: khóa dịch (shift key)

 HELLO với k=3 → KHOOR

# Kết quả
## Sử dụng thuật toán
<img width="823" height="733" alt="{E5C32FB6-62F6-4A02-8C7F-CE8D2D569B32}" src="https://github.com/user-attachments/assets/a3dc4db3-c98c-420f-95da-f5c6285548fe" />
## Đã giải mã
<img width="849" height="690" alt="{F9139622-DF4C-4168-B7FF-0C23689F6A09}" src="https://github.com/user-attachments/assets/115b4b0f-d199-4486-9f7c-d981d442beec" /> 
 ## Đã giải mã bằng C++ 
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
<img width="1514" height="898" alt="{6ED46D9C-DAEF-4E3D-8B65-57FE4D3ECFD0}" src="https://github.com/user-attachments/assets/23066eb1-1a88-46af-bc86-f02943889502" /></p>

# 3. Mã hóa Hoán vị (Columnar transposition (Hoán vị cột)).Hệ thống sẽ dùng thứ tự chữ trong từ để hoán vị cột
Tên: Columnar transposition (Hoán vị cột)
Mã hoá: viết plaintext theo hàng vào ma trận có số cột = len(key); sắp xếp cột theo thứ tự khóa và đọc theo cột
Giải mã: dựa vào chiều dài và thứ tự cột để dựng lại ma trận
Không gian khóa: số hoán vị của số cột: n! (n = chiều dài khóa)
Cách phá: thử các độ dài khóa khả dĩ rồi brute-force hoán vị nhỏ; sử dụng scoring/ngôn ngữ để chọn kết quả.
# Kết Quả
#### Sử dụng mã hóa
<img width="863" height="760" alt="{9EE7D392-8430-4684-B1CE-A24577F7AD3C}" src="https://github.com/user-attachments/assets/7b1332e7-80da-4119-9927-07368ad75584" />
#### Giải mã 
<img width="891" height="710" alt="{EDD29AA9-E5CB-4C9C-ACB3-BE5942BE2D9B}" src="https://github.com/user-attachments/assets/0c8292c1-69ea-4116-9f51-c79e004d1968" />
#### Đã mã hóa và giải mã qua C++
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
<img width="1465" height="707" alt="{FC5CFCDF-00BB-480D-A532-139B3A28F452}" src="https://github.com/user-attachments/assets/a09055f8-5f4b-4510-8e4f-b20bb10ca79a" /></p>

# 4.Mã hóa Vigenère (Vigenère Cipher)Khóa lặp theo chiều dài plaintext
## Cách làm:

Dùng một từ khóa (keyword) để quyết định độ dịch chuyển cho từng ký tự.

Công thức mã hóa: C[i] = (P[i] + K[i]) mod 26

Công thức giải mã: P[i] = (C[i] - K[i] + 26) mod 26

Không gian khóa: 26^m (m = độ dài khóa)

Cách phá: Kasiski + Friedman để tìm m, rồi tách từng Caesar (frequency analysis) hoặc sử dụng tính toán đồng hợp.

Trong đó:

- K[i]: ký tự của khóa (lặp lại nếu cần)

# Kết Quả
## Mã Hóa
<img width="949" height="786" alt="{7F25EA87-6CC2-4E5F-A9CF-8F4CFC3B837A}" src="https://github.com/user-attachments/assets/4082c996-c5b5-4a0e-b8e6-261218054635" />
## Giải mã
<img width="851" height="671" alt="{AF7A5AA5-71F0-4278-98E3-FAE996DF69C5}" src="https://github.com/user-attachments/assets/759921e8-026e-4c8f-b2a9-ceb7454c4e12" /></p>

## Đã mã hóa và giải mã bằng C++
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
<img width="1425" height="811" alt="{66EA4608-FD27-417F-A67B-7C68A5877D83}" src="https://github.com/user-attachments/assets/d65bc3ba-8236-4062-818d-4cd74cdcb3bd" /></p>

## 5. Mã hóa Playfair (Playfair Cipher)

Mã hoá: tạo bảng 5x5 từ khóa (I/J chung). Chia plaintext thành digraph (chèn X nếu cần). Quy tắc: cùng hàng/ cùng cột/ hình chữ nhật.
Giải mã: quy tắc ngược lại.

Không gian khóa: khoảng 25!/(...) rất lớn (phân bố hoán vị của 25 chữ cái), nhưng không gian thực tế nhỏ hơn do cấu trúc bảng.
Cách phá: brute-force không khả thi; sử dụng hill-climbing/heuristic, scoring ngôn ngữ, hoặc tấn công dựa trên phân tích digraph.</p>

## Dùng một ma trận 5x5 chứa các chữ cái để mã hóa cặp ký tự (digraph).

Quy tắc:

1. Nếu 2 ký tự trùng nhau → chèn X vào.

2. Nếu cùng hàng → thay bằng ký tự bên phải.

3. Nếu cùng cột → thay bằng ký tự bên dưới.

4. Nếu khác hàng khác cột → thay bằng ký tự cùng hàng nhưng cột của ký tự kia.

# Kết Quả

## Mã hóa 
<img width="926" height="660" alt="{15AA732D-AA79-4642-900C-A684C24C21EB}" src="https://github.com/user-attachments/assets/5253b234-8907-46b2-a59d-6b986b31b8b5" />

## Giải mã 
<img width="850" height="692" alt="{CBD7BF94-11E4-468B-BE41-B817426C7035}" src="https://github.com/user-attachments/assets/0fcb40f6-9be7-4d7e-aec5-f0fe7a4322d7" /></p>

### Đã mã hóa và giải mã bằng C++
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
<img width="916" height="483" alt="{E7098335-D681-4AC2-908C-CE222709BDE7}" src="https://github.com/user-attachments/assets/b4b820c1-33fd-4d9a-b3cc-aa9b152c43a1" /></p>


