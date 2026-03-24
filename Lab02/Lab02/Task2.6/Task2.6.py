import random

# ==========================================
# 1. KIỂM TRA SỐ NGUYÊN TỐ (Miller-Rabin)
# ==========================================
def is_prime_miller_rabin(n, k=5):
    if n <= 1: return False
    if n <= 3: return True
    if n % 2 == 0: return False

    # Phân tích n - 1 = 2^r * d
    r, d = 0, n - 1
    while d % 2 == 0:
        r += 1
        d //= 2

    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, d, n) # Tính a^d mod n
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

# Yêu cầu 1.1: Tạo số nguyên tố ngẫu nhiên có số bit xác định
def generate_n_bit_prime(bits):
    while True:
        # Tạo một số ngẫu nhiên có số bit tương ứng và đảm bảo nó là số lẻ
        num = random.getrandbits(bits)
        num |= (1 << bits - 1) | 1 
        if is_prime_miller_rabin(num):
            return num

# ==========================================
# 2. TÌM ƯỚC CHUNG LỚN NHẤT (Thuật toán Euclid)
# ==========================================
def gcd_euclid(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# ==========================================
# 3. TÍNH LŨY THỪA MODULO (Modular Exponentiation)
# ==========================================
def mod_exp(a, x, p):
    result = 1
    a = a % p
    while x > 0:
        if x % 2 == 1: 
            result = (result * a) % p
        x = x // 2     
        a = (a * a) % p
    return result

# ==========================================
# CHẠY THỬ NGHIỆM CÁC YÊU CẦU
# ==========================================
if __name__ == "__main__":
    print("--- YÊU CẦU 1: SỐ NGUYÊN TỐ ---")
    print(f"Số nguyên tố 8-bit:  {generate_n_bit_prime(8)}")
    print(f"Số nguyên tố 16-bit: {generate_n_bit_prime(16)}")
    print(f"Số nguyên tố 64-bit: {generate_n_bit_prime(64)}")

    # Yêu cầu 1.2: 10 số nguyên tố lớn nhất nhỏ hơn số nguyên tố Mersenne thứ 10
    # Số nguyên tố Mersenne thứ 10 là M_89 = 2^89 - 1
    m10 = (1 << 89) - 1
    print(f"\nSố nguyên tố Mersenne thứ 10 là: 2^89 - 1")
    
    primes_list = []
    # Bắt đầu kiểm tra từ M10 - 2 (do M10 là số lẻ, ta chỉ kiểm tra các số lẻ nhỏ hơn nó)
    candidate = m10 - 2
    while len(primes_list) < 10:
        if is_prime_miller_rabin(candidate):
            primes_list.append(candidate)
        candidate -= 2
    
    print("10 số nguyên tố lớn nhất nhỏ hơn M10:")
    for i, p in enumerate(primes_list, 1):
        print(f"{i}. {p}")

    # Yêu cầu 1.3: Kiểm tra một số nguyên tùy ý < 2^89 - 1
    test_num = 1234567890123456789
    is_prime = is_prime_miller_rabin(test_num)
    print(f"\nSố {test_num} có phải là số nguyên tố không? {'Có' if is_prime else 'Không'}")

    print("\n--- YÊU CẦU 2: ƯỚC CHUNG LỚN NHẤT (GCD) ---")
    num1 = 123456789012345678901234567890
    num2 = 987654321098765432109876543210
    print(f"GCD của\n{num1} \nvà\n{num2} \nlà: {gcd_euclid(num1, num2)}")

    print("\n--- YÊU CẦU 3: LŨY THỪA MODULO ---")
    # Tính 7^40 mod 19
    a, x, p = 7, 40, 19
    print(f"{a}^{x} mod {p} = {mod_exp(a, x, p)}")
