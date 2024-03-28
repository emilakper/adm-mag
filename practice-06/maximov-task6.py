# Максимов Иван, БПМ-22-4

def generate_combination(n, k, current_combination, result):
    if len(current_combination) == k:
        result.append(list(current_combination))
        return
    
    for i in range(len(n)):
        current_combination.append(n[i])
        generate_combination(n, k, current_combination, result)
        current_combination.pop()

n = int(input("Введите количество чисел: "))
ar = list(map(int, input("Введите числа-элементы: ").split()))
k = int(input("Введите количество элементов в комбинации: "))

combinations = []
generate_combination(ar, k, [], combinations)
print("Всего комбинаций:", len(combinations))
print("Комбинации:")
for combination in combinations:
    print(' '.join(map(str, combination)))

