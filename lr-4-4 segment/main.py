# Программирование на языке высокого уровня (Python).
# Задание №4. Вариант 2
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com

from abstract_linesegment import LineSegment

def test_line_segment_operations():
    # Создание объектов
    line1 = LineSegment(1, 5)
    line2 = LineSegment(4, 8)

    # Проверка строкового представления
    print(f"Line 1: {line1}")
    print(f"Line 2: {line2}")

    # Операция сложения отрезков (объединение)
    line3 = line1 + line2
    print(f"Union of Line 1 and Line 2: {line3}")

    # Операция вычитания отрезков
    line4 = line1 - line2
    print(f"Difference of Line 1 and Line 2: {line4}")

    # Проверка длины отрезка
    print(f"Length of Line 1: {line1.length()}")

    # Сохранение объекта в JSON
    line1.save("line1.json")

    # Загрузка объекта из JSON
    loaded_line = LineSegment.load("line1.json")
    print(f"Loaded Line: {loaded_line}")

if __name__ == "__main__":
    test_line_segment_operations()
