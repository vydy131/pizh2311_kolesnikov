import re
from functools import total_ordering
from typing import Dict, List

@total_ordering
class Roman:
    """Класс для представления римского числа с поддержкой арифметических операций и сравнения."""

    _roman_to_int: Dict[str, int] = {
        'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000
    }
    _int_to_roman: Dict[int, str] = {
        1: 'I', 4: 'IV', 5: 'V', 9: 'IX', 10: 'X', 40: 'XL', 50: 'L',
        90: 'XC', 100: 'C', 400: 'CD', 500: 'D', 900: 'CM', 1000: 'M'
    }

    def __init__(self, value: str) -> None:
        """Инициализирует объект римского числа.

        Args:
            value (str): Римское число в строковом формате.
        """
        if not self.is_valid_roman(value):
            raise ValueError(f"Некорректное римское число: {value}")
        self._value: int = self.roman_to_int(value)

    @staticmethod
    def is_valid_roman(roman: str) -> bool:
        """Проверяет, является ли строка корректным римским числом.

        Args:
            roman (str): Строка с римским числом.

        Returns:
            bool: True, если строка является римским числом, иначе False.
        """
        roman_pattern = r"^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$"
        return bool(re.fullmatch(roman_pattern, roman))

    @staticmethod
    def roman_to_int(roman: str) -> int:
        """Преобразует римское число в десятичное."""
        total = 0
        prev_value = 0
        for char in reversed(roman):
            current = Roman._roman_to_int[char]
            if current < prev_value:
                total -= current
            else:
                total += current
            prev_value = current
        return total

    @staticmethod
    def int_to_roman(number: int) -> str:
        """Преобразует десятичное число в римское."""
        if number <= 0:
            raise ValueError("Римские числа должны быть положительными.")
        result = ""
        for value in sorted(Roman._int_to_roman.keys(), reverse=True):
            while number >= value:
                result += Roman._int_to_roman[value]
                number -= value
        return result

    @staticmethod
    def combine_romans(roman_list: List[str]) -> str:
        """Складывает несколько римских чисел и возвращает результат в римской системе."""
        total = sum(Roman.roman_to_int(roman) for roman in roman_list)
        return Roman.int_to_roman(total)

    @staticmethod
    def extract_romans(text: str) -> List["Roman"]:
        """Извлекает римские числа из текста и возвращает список объектов Roman.

        Args:
            text (str): Исходный текст.

        Returns:
            List[Roman]: Список объектов Roman.
        """
        matches = re.findall(r'\b[IVXLCDM]+\b', text)  # Ищем слова, содержащие только IVXLCDM
        return [Roman(match) for match in matches if Roman.is_valid_roman(match)]

    def to_int(self) -> int:
        """Возвращает арабское представление римского числа"""
        return self._value

    def __add__(self, other: "Roman") -> "Roman":
        return Roman(self.int_to_roman(self._value + other._value))

    def __sub__(self, other: "Roman") -> "Roman":
        result = max(1, self._value - other._value)
        return Roman(self.int_to_roman(result))

    def __mul__(self, other: "Roman") -> "Roman":
        return Roman(self.int_to_roman(self._value * other._value))

    def __truediv__(self, other: "Roman") -> "Roman":
        result = max(1, self._value // other._value)
        return Roman(self.int_to_roman(result))

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Roman):
            return NotImplemented
        return self._value == other._value

    def __lt__(self, other: object) -> bool:
        if not isinstance(other, Roman):
            return NotImplemented
        return self._value < other._value

    def __str__(self) -> str:
        return self.int_to_roman(self._value)

    def __repr__(self) -> str:
        return f"Roman('{self.int_to_roman(self._value)}')"


r = Roman("CMXLIV")  # 944
print(r)  # "CMXLIV"

value = Roman.roman_to_int("MCMXC")  # 1990
print(value)  # 1990

roman_str = Roman.int_to_roman(2024)
print(roman_str)  # "MMXXIV"

print(Roman.is_valid_roman("MMXXIV"))  # True
print(Roman.is_valid_roman("ABC"))  # False

r1 = Roman("X")  # 10
r2 = Roman("V")  # 5
r3 = r1 + r2  # 10 + 5 = 15 ("XV")
print(r3)  # "XV"

r1 = Roman("XX")  # 20
r2 = Roman("X")   # 10
r3 = r1 - r2      # 20 - 10 = 10 ("X")
print(r3)  # "X"

r1 = Roman("X")  # 10
r2 = Roman("V")  # 5
r3 = r1 * r2  # 10 * 5 = 50 ("L")
print(r3)  # "L"

r1 = Roman("X")  # 10
r2 = Roman("II")  # 2
r3 = r1 / r2  # 10 / 2 = 5 ("V")
print(r3)  # "V"

r1 = Roman("X")  # 10
r2 = Roman("V")  # 5
print(r1 > r2)  # True
print(r1 == Roman("X"))  # True
print(r1 < Roman("L"))  # True


text = "Число MMXXIV больше чем CMXCV."
romans = Roman.extract_romans(text)
for roman in romans:
    print(roman)  # MMXXIV, MCMXCV
