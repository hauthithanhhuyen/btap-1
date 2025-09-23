# btap-1
k225480106027 hầu thanh huyền
## Sử dụng các phương pháp: caesar, Affine, hoán vị, vigen, playfair
## githup: 
- mỗi phương pháp làm 1 file riêng( làm về mã hóa 1 chuỗi kí tự)
- trình bày lại phương pháp mã hóa
- Cài đặt mã hóa bao gồm cả endcode và decode ( dùng js/c#/C++/..)
- Chạy ảnh kết quả
### Encrypt (mã hoá): chuyển dữ liệu rõ (plaintext) thành dữ liệu đã được mã (ciphertext) bằng một thuật toán và (thường) một khóa, để che giấu nội dung.
### Decrypt (giải mã): đảo lại quá trình mã hoá, dùng thuật toán và khóa thích hợp để lấy lại plaintext từ ciphertext.
## Bài Làm
##  1. Mã hóa Affine (Affine Cipher)
Cách làm Mỗi ký tự được biến đổi bằng công thức tuyến tính.
Công thức mã hóa: C = (a*P + b) mod 26
Công thức giải mã: P = a⁻¹ * (C - b) mod 26
Không gian khóa: phi(26)26 = 1226 = 312 (a có 12 lựa chọn, b 0..25)
Cách phá: thử tất cả cặp (a,b) (brute-force 312); phân tích tần suất.
### Kết Quả Hiển Thị
 #### Sử dụng thuật toán
 <img width="951" height="654" alt="image" src="https://github.com/user-attachments/assets/785ad226-496b-4589-abbe-d61657de5db9" />
#### Đã giải mã 
<img width="944" height="609" alt="image" src="https://github.com/user-attachments/assets/62f4f914-6b52-461d-8286-ba97f6e89e47" />

## 2. Mã hóa Caesar (Caesar Cipher)
### Cách làm:
Dịch chuyển mỗi ký tự trong bản rõ một số vị trí trong bảng chữ cái.
Công thức mã hóa: C = (P + k) mod 26
Công thức giải mã: P = (C - k + 26) mod 26
Không gian khóa: 25 (k=1..25)
Cách phá: brute-force thử 25 shift; phân tích tần suất để chọn dịch phù hợp.
Trong đó:
- P: ký tự bản rõ (Plaintext)
- C: ký tự bản mã (Ciphertext)
- k: khóa dịch (shift key)
 HELLO với k=3 → KHOOR
### Kết quả
#### Sử dụng thuật toán
<img width="1187" height="730" alt="image" src="https://github.com/user-attachments/assets/bd7c34f2-9275-4449-a5cf-021213704158" />
#### Đã giải mã
<img width="966" height="649" alt="image" src="https://github.com/user-attachments/assets/a8110f6e-478e-42b9-aae2-6f572f6c11b8" />

## 3. Mã hóa Hoán vị (Columnar transposition (Hoán vị cột)).Hệ thống sẽ dùng thứ tự chữ trong từ để hoán vị cột
Tên: Columnar transposition (Hoán vị cột)
Mã hoá: viết plaintext theo hàng vào ma trận có số cột = len(key); sắp xếp cột theo thứ tự khóa và đọc theo cột
Giải mã: dựa vào chiều dài và thứ tự cột để dựng lại ma trận
Không gian khóa: số hoán vị của số cột: n! (n = chiều dài khóa)
Cách phá: thử các độ dài khóa khả dĩ rồi brute-force hoán vị nhỏ; sử dụng scoring/ngôn ngữ để chọn kết quả.

## Kết Quả
#### Sử dụng mã hóa <img width="913" height="574" alt="image" src="https://github.com/user-attachments/assets/8756c6e0-5d82-4024-82ba-7998a5411fc1" />
#### Giải mã <img width="943" height="545" alt="image" src="https://github.com/user-attachments/assets/01d8ab10-fe89-4b1e-b4fb-8cd70029e839" />

## 4.Mã hóa Vigenère (Vigenère Cipher)Khóa lặp theo chiều dài plaintext
### Cách làm:
Dùng một từ khóa (keyword) để quyết định độ dịch chuyển cho từng ký tự.
Công thức mã hóa: C[i] = (P[i] + K[i]) mod 26
Công thức giải mã: P[i] = (C[i] - K[i] + 26) mod 26
Không gian khóa: 26^m (m = độ dài khóa)
Cách phá: Kasiski + Friedman để tìm m, rồi tách từng Caesar (frequency analysis) hoặc sử dụng tính toán đồng hợp.
Trong đó:
- K[i]: ký tự của khóa (lặp lại nếu cần)
## Kết Quả
#### Mã Hóa <img width="1087" height="622" alt="image" src="https://github.com/user-attachments/assets/3baf7a48-0ed9-4905-8349-239e4f8cbe6d" />
#### Giải mã <img width="960" height="611" alt="image" src="https://github.com/user-attachments/assets/b212a8ee-79f8-4f14-9064-2096e9e0ae02" />

## 5. Mã hóa Playfair (Playfair Cipher)
Mã hoá: tạo bảng 5x5 từ khóa (I/J chung). Chia plaintext thành digraph (chèn X nếu cần). Quy tắc: cùng hàng/ cùng cột/ hình chữ nhật.
Giải mã: quy tắc ngược lại.
Không gian khóa: khoảng 25!/(...) rất lớn (phân bố hoán vị của 25 chữ cái), nhưng không gian thực tế nhỏ hơn do cấu trúc bảng.
Cách phá: brute-force không khả thi; sử dụng hill-climbing/heuristic, scoring ngôn ngữ, hoặc tấn công dựa trên phân tích digraph.
### Dùng một ma trận 5x5 chứa các chữ cái để mã hóa cặp ký tự (digraph).
Quy tắc:
1. Nếu 2 ký tự trùng nhau → chèn X vào.
2. Nếu cùng hàng → thay bằng ký tự bên phải.
3. Nếu cùng cột → thay bằng ký tự bên dưới.
4. Nếu khác hàng khác cột → thay bằng ký tự cùng hàng nhưng cột của ký tự kia.
## Kết Quả
## Mã hóa <img width="941" height="733" alt="image" src="https://github.com/user-attachments/assets/99042e16-8119-420c-8b06-f30bf5eaf21f" />
## Giải mã <img width="1010" height="578" alt="image" src="https://github.com/user-attachments/assets/266f3926-a744-49fc-9544-efdeec3f4ae6" />


