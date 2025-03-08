# Программирование на языке высокого уровня (Python).
# Задание №6. Вариант 2
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com

from writing_instruments import Pencil, Pen, GelPen

def main():
    pencil = Pencil(color="черный", width=0.5, hardness="HB")
    pen = Pen(color="синий", width=0.7, ink_type="гелевые чернила")
    gel_pen = GelPen(color="красный", width=0.8, ink_type="гель", gel_quality="высокое")

    pencil.write()
    pen.write()
    gel_pen.write()

    pencil.sharpen()
    pen.refill()
    gel_pen.smooth_write()

if __name__ == "__main__":
    main()
