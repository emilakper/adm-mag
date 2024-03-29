# Гончаровский Максим, БПМ-22-4, вариант 7.

# Функция генерации всех разбиений числа num.
def MakeSplittings(num):
    # current - текущее разбиение. Инициализируется как массив из num единиц - самое первое разбиение числа num.
    current = [1 for i in range(num)]
    # splitings - итоговый ответ, массив всех разбиений числа
    splittings = []
    splittings.append(current.copy())

    # Будем строить разбиения до тех пор, пока не дойдём до конечного разбиения вида [num],
    # т.е состоящего из одного числа, его самого
    while (current[0] != num):
        # Сперва ищем первый минимальный элемент текущего разбиения(не считая последний элемент)
        minim = 1000000000
        minim_indx = -1
        for i in range(len(current) - 1):
            if current[i] < minim:
                minim = current[i]
                minim_indx = i

        # Переносим единицу из последнего элемента в найденный минимальный элемент.
        # Если последний элемент единица, то удаляем его. Если нет, то просто уменьшаем на 1.
        current[minim_indx] += 1
        if current[-1] == 1:
            current.pop()
        else:
            current[-1] -= 1

        # Затем все элементы после минимального заменяем нужным количеством единиц(чтобы в сумме было num)
        ones = sum(current[minim_indx + 1:])
        current = current[: minim_indx + 1] + [1 for i in range(ones)]

        # Добавляем новое найденное разбиение в массив
        splittings.append(current.copy())

    return splittings

# Вывод полученных разбиений
def PrintSplittings(splittings):
    print(f"Количество полученных разбиений числа {sum(splittings[0])} : {len(splittings)}")
    print("Полученные разбиения:")
    for i in splittings:
        print(i)

# Функция генерации композиции числа num
# В ней будут сначала генерироваться все разбиения числа num, а потом для каждого разбиения будут находиться
# всевозможные перестановки. Совокупность этих перестанок - композиция числа num.
def MakeCompositions(num):
    splittings = MakeSplittings(num)
    compositions = []

    for i in splittings:
        permutations = MakeUniquePermutations(i)
        for j in permutations:
            compositions.append(j.copy())

    return compositions

def PrintCompositions(compositions):
    print(f"Количество композиций числа {sum(compositions[0])} : {len(compositions)}")
    print("Полученные разбиения:")
    for i in compositions:
        print(i)



# Функция для генерации уникальных перестановок элементов массива
def MakeUniquePermutations(arr):
    if len(arr) == 1:
        return [arr]

    unique_permutations_list = []
    for i, v in enumerate(arr):
        if i > 0 and arr[i] == arr[i - 1]:
            continue  # Пропускаем повторяющиеся элементы

        remaining_elements = arr[:i] + arr[i + 1:]
        remaining_permutations = MakeUniquePermutations(remaining_elements)

        for perm in remaining_permutations:
            unique_permutations_list.append([v] + perm)

    return unique_permutations_list

if __name__ == "__main__":
    print("Введите число для нахождения разбиений и композиций = ", end=' ')
    num = int(input())
    PrintSplittings(MakeSplittings(num))
    PrintCompositions(MakeCompositions(num))