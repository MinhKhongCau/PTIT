import csv
import os

# Load data to train

# Define the folder path
folder_path = "hash/agorithm-1/train/"  # Change this to your actual folder path
folder_data_path = "hash/agorithm-1/train_csv/"  # Change this to your actual folder path

# Loop through all files in the folder
for filename in os.listdir(folder_path):
    input_file = os.path.join(folder_path, filename)  # Full file path
    # Define the file path
    output_file = os.path.join(folder_data_path, filename + '.csv')
    title = ['hash','rand_val']

    # Check if it's a file (not a folder)
    if os.path.isfile(input_file):

        # Open and read the file
        with open(input_file, "r") as file, open(output_file, "w", newline="") as csv_file:
            writer = csv.writer(csv_file)
            
            writer.writerow(title)

            for line in file:

                line = line.strip()  # Remove any extra spaces or newlines
                if ":" in line:  # Check if line has hash and salt
                    hash_value, rand_val = line.split(":", 1)  # Split only on the first ":"
                    print(f"Hash: {hash_value}\nrand_val: {rand_val}\n")
                else:
                    print(f"Hash: {line}\n(No rand_val found)\n")

                writer.writerow([hash_value, rand_val])




# Load data to test
# Define the folder path
folder_path = "hash/agorithm-1/test/"  # Change this to your actual folder path
folder_data_path = "hash/agorithm-1/test_csv/"  # Change this to your actual folder path

# Loop through all files in the folder
for filename in os.listdir(folder_path):
    input_file = os.path.join(folder_path, filename)  # Full file path
    # Define the file path
    output_file = os.path.join(folder_data_path, filename + '.csv')

    # Check if it's a file (not a folder)
    if os.path.isfile(input_file):

        # Open and read the file
        with open(input_file, "r") as file, open(output_file, "w", newline="") as csv_file:
            title = ['hash', 'rand_val']

            writer = csv.writer(csv_file)

            writer.writerow(title)
            for line in file:

                line = line.strip()  # Remove any extra spaces or newlines
                if ":" in line:  # Check if line has hash and salt
                    hash_value, rand_val = line.split(":", 1)  # Split only on the first ":"
                    print(f"Hash: {hash_value}\nRand_val: {rand_val}\n")
                else:
                    print(f"Hash: {line}\n(No rand_val found)\n")

                writer.writerow([hash_value, rand_val])
