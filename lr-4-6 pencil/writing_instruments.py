from abc import ABC, abstractmethod

class WritingInstrument(ABC):
    def __init__(self, color: str, width: float):
        self.color = color
        self._width = width
        self.__type = "Unknown"

    @abstractmethod
    def write(self):
        pass

    @property
    def width(self):
        return self._width

    @width.setter
    def width(self, value):
        if value <= 0:
            raise ValueError("Ширина должна быть положительным числом.")
        self._width = value

    def set_type(self, type_name):
        """Устанавливаем тип принадлежности (для внутреннего использования)"""
        self.__type = type_name

    def get_type(self):
        """Получаем тип принадлежности"""
        return self.__type

class Pencil(WritingInstrument):
    def __init__(self, color: str, width: float, hardness: str):
        super().__init__(color, width)
        self.hardness = hardness      # Жесткость грифеля

        self.set_type("Карандаш")

    def write(self):
        print(f"Карандаш пишет {self.color} цветом и жесткостью {self.hardness} с шириной {self.width} мм.")

    def sharpen(self):
        """Дополнительный метод для точения карандаша"""
        print("Карандаш затачен.")

class Pen(WritingInstrument):
    def __init__(self, color: str, width: float, ink_type: str):
        super().__init__(color, width)
        self.ink_type = ink_type      # Тип чернил

        self.set_type("Ручка")

    def write(self):
        print(f"Ручка пишет {self.color} чернилами и типом {self.ink_type} с шириной {self.width} мм.")

    def refill(self):
        """Метод для заправки ручки"""
        print("Ручка заправлена.")

class GelPen(Pen):
    def __init__(self, color: str, width: float, ink_type: str, gel_quality: str):
        super().__init__(color, width, ink_type)
        self.gel_quality = gel_quality  # Качество геля

        self.set_type("Гелевая Ручка")

    def write(self):
        print(f"Гелевая ручка пишет {self.color} гелем с качеством {self.gel_quality} и шириной {self.width} мм.")

    def smooth_write(self):
        """Метод для плавного письма"""
        print("Гелевая ручка пишет плавно и без рывков.")
