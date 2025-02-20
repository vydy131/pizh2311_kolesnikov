from functools import total_ordering

class Being:
    """Abstract Being"""
    def __init__(self, height: int, name: str) -> None:
        self._height: int = height
        self._name: str = name

    @property
    def height(self) -> int:
        return self._height

    @property
    def name(self) -> str:
        return self._name


@total_ordering
class GoodIfrit(Being):
    """Extends Being"""
    def __init__(self, height: int, name: str, goodness: int) -> None:
        super().__init__(height, name)
        self._goodness: int = max(0, goodness)

    @property
    def goodness(self) -> int:
        return self._goodness

    def change_goodness(self, value: int) -> None:
        """Меняет доброту на указанную величину (не может быть меньше 0)"""
        self._goodness = max(0, self._goodness + value)

    def __add__(self, number: int) -> "GoodIfrit":
        """Перегрузка оператора + (создает нового ифрита с увеличенной высотой)"""
        return GoodIfrit(self._height + number, self._name, self._goodness)

    def __call__(self, value: int) -> float:
        """Вызываемый метод: возвращает доброту, деленную на высоту"""
        return self._goodness * value / self._height

    def __str__(self) -> str:
        """Возвращает строковое представление объекта"""
        return f"Good Ifrit {self._name}, height {self._height}, goodness {self._goodness}"

    def __eq__(self, other: object) -> bool:
        """Равенство по доброте, высоте и имени"""
        if not isinstance(other, GoodIfrit):
            return NotImplemented
        return (self._goodness, self._height, self._name) == (other._goodness, other._height, other._name)

    def __lt__(self, other: object) -> bool:
        """Сравнение: сначала по доброте, затем по высоте, затем по имени"""
        if not isinstance(other, GoodIfrit):
            return NotImplemented
        return (self._goodness, self._height, self._name) < (other._goodness, other._height, other._name)


gi: GoodIfrit = GoodIfrit(80, "Hazrul", 3)
gi.change_goodness(4)
print(gi)  # Good Ifrit Hazrul, height 80, goodness 7
gi = gi + 15
print(gi)  # Good Ifrit Hazrul, height 95, goodness 7
print(gi(31))  # 2.28 (примерное значение)

gi1: GoodIfrit = GoodIfrit(80, "Hazrul", 3)
gi2: GoodIfrit = GoodIfrit(80, "Dalziel", 1)
print(gi1 < gi2)  # False
gi1.change_goodness(2)
print(gi1 > gi2)  # True
print(gi1, gi2, sep='\n')
