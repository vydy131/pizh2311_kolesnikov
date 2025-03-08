# Программирование на языке высокого уровня (Python).
# Задание №5. Вариант 2
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com

import json
from abstract_linesegment import LineSegment

class LineSegmentCollection:
    def __init__(self):
        self._data = []

    def __str__(self):
        return f"LineSegmentCollection({', '.join(str(segment) for segment in self._data)})"

    def __getitem__(self, index):
        """Обработка индексации и срезов"""
        return self._data[index]

    def add(self, value):
        """Добавление объекта LineSegment в коллекцию"""
        if not isinstance(value, LineSegment):
            raise TypeError("Only LineSegment objects can be added")
        self._data.append(value)

    def remove(self, index):
        """Удаление объекта LineSegment по индексу"""
        if index < 0 or index >= len(self._data):
            raise IndexError("Index out of range")
        del self._data[index]

    def save(self, filename):
        """Сохранение коллекции объектов в JSON-файл"""
        with open(filename, "w") as f:
            data = [{"start": segment.start, "end": segment.end} for segment in self._data]
            json.dump(data, f)

    @classmethod
    def load(cls, filename):
        """Загрузка коллекции объектов из JSON-файла"""
        with open(filename, "r") as f:
            data = json.load(f)
            collection = cls()
            for item in data:
                collection.add(LineSegment(item["start"], item["end"]))
            return collection
