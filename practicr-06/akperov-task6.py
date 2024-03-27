# Инициализируем строку direction, которая представляет все направления.
direction = "DLRU"

# Массивы для представления изменений в строках и столбцах
dr = [1, 0, 0, -1]
dc = [0, -1, 1, 0]

# Функция для проверки, находится ли ячейка (строка, столбец) внутри лабиринта и не заблокирована ли
def is_valid(row, col, n, maze):
    return 0 <= row < n and 0 <= col < n and maze[row][col] == 1

# Функция для получения всех допустимых путей
def find_path(row, col, maze, n, ans, current_path):
    # Если мы достигли нижней правой ячейки матрицы, добавляем
    # текущий путь в ans и возвращаемся
    if row == n - 1 and col == n - 1:
        ans.append(current_path)
        return
    # Помечаем текущую ячейку как заблокированную
    maze[row][col] = 0

    for i in range(4):
        # Находим следующую строку на основе текущей строки (row)
        # и массива dr
        next_row = row + dr[i]
        # Находим следующий столбец на основе текущего столбца
        # (col) и массива dc[]
        next_col = col + dc[i]

        # Проверяем, является ли следующая ячейка допустимой
        if is_valid(next_row, next_col, n, maze):
            current_path += direction[i]
            # Рекурсивно вызываем функцию findpath для
            # следующей ячейки
            find_path(next_row, next_col, maze, n, ans, current_path)
            #  Удаляем последнее направление при возврате
            current_path = current_path[:-1]

    # Помечаем текущую ячейку как разблокированную
    maze[row][col] = 1


def print_paths(result):
    if not result:
        print(-1)
    else:
        for path in result:
            path_str = " -> ".join(path)
            path_str = path_str.replace("D", "Вниз").replace("R", "Вправо").replace("L", "Влево").replace("U", "Вверх")
            print(path_str)

# Ввод лабиринта от пользователя
n = int(input("Введите размер лабиринта: "))
maze = []
print("Введите строки лабиринта (1 - проходимая ячейка, 0 - непроходимая ячейка):")
for _ in range(n):
    row = list(map(int, input().split()))
    maze.append(row)

# Ввод начальной и конечной позиции от пользователя
start_row, start_col = map(int, input("Введите начальную позицию (строка столбец): ").split())
end_row, end_col = map(int, input("Введите конечную позицию (строка столбец): ").split())

# Список для хранения всех допустимых путей
result = []
# Храним текущий путь
current_path = ""

if maze[start_row][start_col] != 0 and maze[end_row][end_col] != 0:
    find_path(start_row, start_col, maze, n, result, current_path)

print_paths(result)