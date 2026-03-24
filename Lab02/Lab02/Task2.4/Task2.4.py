import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

print("--- HƯỚNG DẪN BÀI 2.4: ERROR PROPAGATION ---")
print("Chương trình này sẽ tự động:")
print("1. Tạo 1000 byte dữ liệu ngẫu nhiên.")
print("2. Mã hóa dữ liệu bằng thuật toán AES-128.")
print("3. Làm hỏng bản mã bằng cách đảo 1 bit tại byte thứ 26.")
print("4. Giải mã và thống kê số khối (block) bị hỏng trên các chế độ ECB, CBC, CFB, OFB.")
input("Vui lòng nhấn phím Enter để bắt đầu chạy mô phỏng...")
print("\nĐang xử lý...")

key = os.urandom(16)
iv = os.urandom(16)
plaintext = os.urandom(1000)
padded_pt = pad(plaintext, AES.block_size)

modes = {
    "ECB": AES.MODE_ECB,
    "CBC": AES.MODE_CBC,
    "CFB": AES.MODE_CFB,
    "OFB": AES.MODE_OFB
}

for mode_name, mode_val in modes.items():
    if mode_name == "ECB":
        cipher_encrypt = AES.new(key, mode_val)
        cipher_decrypt = AES.new(key, mode_val)
    else:
        cipher_encrypt = AES.new(key, mode_val, iv=iv)
        cipher_decrypt = AES.new(key, mode_val, iv=iv)
        
    ciphertext = bytearray(cipher_encrypt.encrypt(padded_pt))
    ciphertext[25] ^= 0x01
    
    decrypted_padded_pt = cipher_decrypt.decrypt(bytes(ciphertext))
    
    corrupted_blocks = 0
    total_blocks = len(padded_pt) // 16
    
    for i in range(total_blocks):
        orig_block = padded_pt[i*16 : (i+1)*16]
        dec_block = decrypted_padded_pt[i*16 : (i+1)*16]
        if orig_block != dec_block:
            corrupted_blocks += 1
            
    print(f"Chế độ {mode_name}: Số block bản rõ bị hỏng = {corrupted_blocks}")
