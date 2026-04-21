from Crypto.Cipher import AES

key = b'1234567890123456'
plaintext = b"UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_" # 32 bytes
iv = b'0000000000000000' # 16 bytes cho CBC, CFB, OFB
nonce = b'00000000'      # 8 bytes cho CTR (theo mặc định của pycryptodome)

# 1. AES-ECB
cipher_ecb = AES.new(key, AES.MODE_ECB)
ct_ecb = cipher_ecb.encrypt(plaintext)

# 2. AES-CBC
cipher_cbc = AES.new(key, AES.MODE_CBC, iv)
ct_cbc = cipher_cbc.encrypt(plaintext)

# 3. AES-CFB
# CFB xử lý dữ liệu theo từng phần nhỏ, dùng bản mã trước đó làm đầu vào mã hóa tiếp [cite: 182, 185]
cipher_cfb = AES.new(key, AES.MODE_CFB, iv=iv)
ct_cfb = cipher_cfb.encrypt(plaintext)

# 4. AES-OFB
# OFB dùng đầu ra của phép mã hóa trước đó làm đầu vào, và sử dụng toàn bộ khối [cite: 183, 186]
cipher_ofb = AES.new(key, AES.MODE_OFB, iv=iv)
ct_ofb = cipher_ofb.encrypt(plaintext)

# 5. AES-CTR
# CTR mã hóa bằng cách XOR bản rõ với một bộ đếm (counter) được mã hóa, bộ đếm này tăng dần [cite: 184, 187]
cipher_ctr = AES.new(key, AES.MODE_CTR, nonce=nonce)
ct_ctr = cipher_ctr.encrypt(plaintext)

# --- IN KẾT QUẢ ---
def format_blocks(hex_string):
    return ' | '.join(hex_string[i:i+32] for i in range(0, len(hex_string), 32))

print("Plaintext:      ", format_blocks(plaintext.hex()))
print("AES-ECB Result: ", format_blocks(ct_ecb.hex()))
print("AES-CBC Result: ", format_blocks(ct_cbc.hex()))
print("AES-CFB Result: ", format_blocks(ct_cfb.hex()))
print("AES-OFB Result: ", format_blocks(ct_ofb.hex()))
print("AES-CTR Result: ", format_blocks(ct_ctr.hex()))