test_list = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]

n = 3

output = [test_list[i : i + n] for i in range(0, len(test_list), n)]
print(output)