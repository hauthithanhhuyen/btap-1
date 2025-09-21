# btap-1
k225480106027 hầu thanh huyền
## Sử dụng các phương pháp: caesar, Affine, hoán vị, vigen, playfair
## githup: 
- mỗi phương pháp làm 1 file riêng( làm về mã hóa 1 chuỗi kí tự)
- trình bày lại phương pháp mã hóa
- Cài đặt mã hóa bao gồm cả endcode và decode ( dùng js/c#/C++/..)
- Chạy ảnh kết quả
## Bài Làm
##  1 Mã hóa Affine (Affine Cipher)
Cách làm Mỗi ký tự được biến đổi bằng công thức tuyến tính.
Công thức mã hóa: C = (a*P + b) mod 26
Công thức giải mã: P = a⁻¹ * (C - b) mod 26
Trong đó:
- a và b là khóa (với a phải nguyên tố cùng 26)
- a⁻¹: nghịch đảo modulo của a
### Kết Quả Hiển Thị
## <img width="785" height="840" alt="image" src="https://github.com/user-attachments/assets/86cd62e3-00a9-43fc-8479-dee608a526e6" />
## 2. Mã hóa Caesar (Caesar Cipher)
### Cách làm:
Dịch chuyển mỗi ký tự trong bản rõ một số vị trí trong bảng chữ cái.
Công thức mã hóa: C = (P + k) mod 26
Công thức giải mã: P = (C - k + 26) mod 26
Trong đó:
- P: ký tự bản rõ (Plaintext)
- C: ký tự bản mã (Ciphertext)
- k: khóa dịch (shift key)
 HELLO với k=3 → KHOOR
### Kết quả
## <img width="936" height="778" alt="image" src="https://github.com/user-attachments/assets/c798eccb-bda5-4503-85e8-df4864ca3c31" />
## 3. Mã hóa Hoán vị (Permutation Cipher)
### Cách làm:
Sắp xếp lại vị trí các ký tự theo một khóa hoán vị.
Thay vì thay đổi ký tự, ta thay đổi thứ tự ký tự.
## Kết Quả
<img width="681" height="639" alt="image" src="https://github.com/user-attachments/assets/4c0524f1-547a-4fbc-84dd-9f79b9da36c8" />
## 4.Mã hóa Vigenère (Vigenère Cipher)
### Cách làm:
Dùng một từ khóa (keyword) để quyết định độ dịch chuyển cho từng ký tự.
Công thức mã hóa: C[i] = (P[i] + K[i]) mod 26
Công thức giải mã: P[i] = (C[i] - K[i] + 26) mod 26
Trong đó:
- K[i]: ký tự của khóa (lặp lại nếu cần)
## Kết Quả
<img width="803" height="499" alt="image" src="https://github.com/user-attachments/assets/9ae616d4-ad33-4abc-8d5d-0e76958c239b" />
## 5. Mã hóa Playfair (Playfair Cipher)
### Cách làm:
Dùng một ma trận 5x5 chứa các chữ cái để mã hóa cặp ký tự (digraph).
Quy tắc:
1. Nếu 2 ký tự trùng nhau → chèn X vào.
2. Nếu cùng hàng → thay bằng ký tự bên phải.
3. Nếu cùng cột → thay bằng ký tự bên dưới.
4. Nếu khác hàng khác cột → thay bằng ký tự cùng hàng nhưng cột của ký tự kia.
## Kết Quả
<img width="979" height="511" alt="image" src="https://github.com/user-attachments/assets/2dcf6de3-8a6a-4fbd-b95c-73dbb32f4f99" />


