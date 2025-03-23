import pandas as pd
import numpy as np
import random
import json
import math
from collections import Counter


# Danh sách các thuật toán băm phổ biến
hash_algorithms = ["SHA-256", "BLAKE3", "Keccak-256", "SHA3-512", "Whirlpool"]

# Các loại dữ liệu có thể có trong hệ thống
data_types = ["Text", "JSON", "Binary", "Image", "Audio", "Video"]

# Hàm tạo dữ liệu phân phối byte 
def generate_byte_distribution():
    dist = np.random.rand(256)  # Tạo ngẫu nhiên giá trị [0,1] cho 256 byte
    return dist / np.sum(dist)  # Chuẩn hóa thành xác suất

# Hàm tính độ entropy (giả lập)
def calculate_entropy():
    return round(np.random.uniform(30, 50), 2)  # Entropy thường từ 3-8

# Hàm tính độ phức tạp tính toán (giả lập)
def calculate_complexity(data_size, entropy):
    return round((data_size / 1024) * (entropy / 8), 2)  # Quy tắc đơn giản

# Hàm chọn thuật toán băm dựa trên dữ liệu
def select_hash_algorithm(data_size, entropy, complexity_score):
    if complexity_score > 0.8:
        return "SHA3-512"
    elif entropy > 6:
        return "BLAKE3"
    elif data_size > 2048:
        return "Whirlpool"
    elif data_size > 1024:
        return "Keccak-256"
    else:
        return "SHA-256"

# Số lượng mẫu dữ liệu cần tạo
NUM_SAMPLES = 5000

# Danh sách để lưu dataset
dataset = []

# Sinh dữ liệu giả lập
for _ in range(NUM_SAMPLES):
    data_type = random.choice(data_types)
    data_size = random.randint(10000, 50000)  # Kích thước từ 100B đến 5MB
    entropy = calculate_entropy()
    byte_distribution = generate_byte_distribution().tolist()  # Chuyển thành danh sách JSON được
    complexity_score = calculate_complexity(data_size, entropy)
    hash_algorithm = select_hash_algorithm(data_size, entropy, complexity_score)

    dataset.append({
        "data_type": data_type,
        "data_size": data_size,
        "entropy": entropy,
        "byte_distribution": byte_distribution,
        "complexity_score": complexity_score,
        "recommended_hash_algorithm": hash_algorithm
    })

# Lưu dataset dưới dạng CSV
df = pd.DataFrame(dataset)
df.to_csv("generated_hash_dataset.csv", index=False)

# Lưu dataset dưới dạng JSON
with open("generated_hash_dataset.json", "w") as f:
    json.dump(dataset, f, indent=4)

print("Dataset đã được tạo thành công và lưu vào file!")
