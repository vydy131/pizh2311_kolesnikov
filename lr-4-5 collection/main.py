from abstract_linesegment import LineSegment
from line_segment_collection import LineSegmentCollection

def test_line_segment_operations():
    # Пример создания коллекции и добавления отрезков
    collection = LineSegmentCollection()

    # Создаем объекты LineSegment
    line1 = LineSegment(1, 5)
    line2 = LineSegment(6, 10)

    # Добавляем их в коллекцию
    collection.add(line1)
    collection.add(line2)

    # Печать коллекции
    print(collection)

    # Сохранение коллекции в JSON
    collection.save("line_segments.json")

    # Загрузка коллекции из JSON
    loaded_collection = LineSegmentCollection.load("line_segments.json")
    print(loaded_collection)

    # Индексация коллекции
    print(loaded_collection[0])  # Вывод первого элемента коллекции

if __name__ == "__main__":
    test_line_segment_operations()
