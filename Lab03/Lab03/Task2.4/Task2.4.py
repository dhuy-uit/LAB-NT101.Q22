import hashlib

n_hex = "..." 
n = int(n_hex, 16)

e_hex = "10001" 
e = int(e_hex, 16)

S_hex = "..." 
S = int(S_hex, 16)


print("Đang tiến hành xác minh chữ ký chứng chỉ X.509...\n")

EM_prime = pow(S, e, n)

EM_prime_hex = hex(EM_prime)[2:]
print(f"[1] Giá trị sau khi giải mã chữ ký (EM' = S^e mod n):\n{EM_prime_hex}\n")

try:
    with open("c0_body.bin", "rb") as f:
        tbs_data = f.read()
        
    calculated_hash = hashlib.sha256(tbs_data).hexdigest()
    print(f"[2] Mã băm SHA-256 tự tính từ c0_body.bin:\n{calculated_hash}\n")
        
    if EM_prime_hex.endswith(calculated_hash):
        print("=> KẾT LUẬN: Xác minh chữ ký THÀNH CÔNG! Băm khớp nhau, chứng chỉ hợp lệ.")
    else:
        print("=> KẾT LUẬN: Xác minh chữ ký THẤT BẠI! Chứng chỉ có thể đã bị thay đổi hoặc giả mạo.")

except FileNotFoundError:
    print("[LỖI] Không tìm thấy file 'c0_body.bin' trong thư mục hiện tại.")
    print("Vui lòng đảm bảo bạn đã chạy lệnh: openssl asn1parse -i -in c0.pem -strparse 4 -out c0_body.bin -noout")
