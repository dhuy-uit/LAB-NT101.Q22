from Crypto.Cipher import DES

print("--- KẾT QUẢ BÀI 2.3: AVALANCHE EFFECT VỚI DANH SÁCH MSSV ---")

mssv_list = ['24520661', '24520653', '24520514']
p1 = b'STAYHOME'
p2 = b'STAYHOMA'

for mssv in mssv_list:
    key = mssv.encode('utf-8')
    cipher = DES.new(key, DES.MODE_ECB)
    
    c1 = cipher.encrypt(p1)
    c2 = cipher.encrypt(p2)
    
    bin_c1 = bin(int.from_bytes(c1, 'big'))[2:].zfill(64)
    bin_c2 = bin(int.from_bytes(c2, 'big'))[2:].zfill(64)
    
    hd = sum(b1 != b2 for b1, b2 in zip(bin_c1, bin_c2))
    percent = (hd / 64) * 100
    
    print(f"MSSV (Key)      : {mssv}")
    print(f"Bản mã p1 (bin) : {bin_c1}")
    print(f"Bản mã p2 (bin) : {bin_c2}")
    print(f"Số bit thay đổi : {hd}/64")
    print(f"Tỷ lệ thay đổi  : {percent:.2f}%\n")
