from abc import ABC, abstractmethod
import json

class AbstractLineSegment(ABC):
    @abstractmethod
    def length(self):
        """Метод для вычисления длины отрезка"""
        pass

    @abstractmethod
    def intersects(self, other):
        """Метод для проверки пересечения отрезков"""
        pass

    @abstractmethod
    def __str__(self):
        """Метод для строкового представления объекта"""
        pass

    @classmethod
    @abstractmethod
    def from_string(cls, str_value):
        """Метод для создания объекта на основе строки"""
        pass

    @abstractmethod
    def save(self, filename):
        """Метод для сохранения объекта в JSON"""
        pass

    @classmethod
    @abstractmethod
    def load(cls, filename):
        """Метод для загрузки объекта из JSON"""
        pass

class LineSegment(AbstractLineSegment):
    def __init__(self, start, end):
        if start > end:
            raise ValueError("Start point cannot be greater than end point")
        self._start = start
        self._end = end

    def __str__(self):
        return f"[{self._start}, {self._end}]"

    @property
    def start(self):
        return self._start

    @property
    def end(self):
        return self._end

    def __add__(self, other):
        """Объединение двух отрезков"""
        if not isinstance(other, LineSegment):
            raise TypeError("Can only add another LineSegment")
        return LineSegment(min(self.start, other.start), max(self.end, other.end))

    def __sub__(self, other):
        """Вычитание отрезков"""
        if not isinstance(other, LineSegment):
            raise TypeError("Can only subtract another LineSegment")
        if self.intersects(other):
            return LineSegment(min(self.start, other.start), min(self.end, other.end))
        return self

    def intersects(self, other):
        """Проверка пересечения отрезков"""
        return not (self.end < other.start or self.start > other.end)

    def length(self):
        """Вычисление длины отрезка"""
        return self.end - self.start

    @classmethod
    def from_string(cls, str_value):
        """Создание объекта на основе строки"""
        try:
            start, end = map(int, str_value.strip("[]").split(","))
            return cls(start, end)
        except ValueError:
            raise ValueError("Invalid string format")

    def save(self, filename):
        """Сохранение объекта в JSON-файл"""
        with open(filename, "w") as f:
            json.dump({"start": self.start, "end": self.end}, f)

    @classmethod
    def load(cls, filename):
        """Загрузка объекта из JSON-файла"""
        with open(filename, "r") as f:
            data = json.load(f)
            return cls(data["start"], data["end"])
