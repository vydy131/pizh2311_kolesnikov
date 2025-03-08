# Программирование на языке высокого уровня (Python).
# Задание №2.
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com

from Order import Order
from Pizza import PizzaPeperoni, PizzaSea, PizzaBBQ

class Terminal:
    COMPANY_NAME = "Пиццерия #1"
    ORDER_REJECT_CODE = "-1"
    ORDER_CONFIRM_CODE = "0"

    def __init__(self):
        self.menu = [PizzaPeperoni(), PizzaBBQ(), PizzaSea()]
        self.order = Order()
        self.isShowMenu = True

    def __str__(self):
        return f"{self.COMPANY_NAME} — Terminal заказа пиццы"

    def showMenu(self):
        if not self.isShowMenu:
            return
        print("\n" + "-" * 50)
        print(f"{self.COMPANY_NAME}\nДобро пожаловать!\n")
        print("Меню:")
        for i, pizza in enumerate(self.menu, start=1):
            print(f"{i}. {pizza}")
        print("Для выбора укажите цифру через <ENTER>.")
        print(f"Для отмены заказа введите {self.ORDER_REJECT_CODE}")
        print(f"Для подтверждения заказа введите {self.ORDER_CONFIRM_CODE}")
        self.isShowMenu = False

    def command(self, menuPosition):
        if menuPosition == self.ORDER_REJECT_CODE:
            print("Order отменён.")
            self.order = Order()
            self.isShowMenu = True
        elif menuPosition == self.ORDER_CONFIRM_CODE:
            print(self.order)
            amount = float(input("Введите сумму: "))
            change = amount - self.order.amount()
            if change < 0:
                print("В убыток не работаем")
                raise ValueError
            print(f"Вы внесли {amount:.2f} р. Сдача: {change:.2f} р.")
            self.order.execute()
            self.order = Order()
            self.isShowMenu = True
        else:
            try:
                index = int(menuPosition) - 1
                if 0 <= index < len(self.menu):
                    self.order.add(self.menu[index])
                else:
                    print("Некорректный ввод.")
            except ValueError:
                print("Некорректный ввод.")


if __name__ == "__main__":
    terminal1 = Terminal()
    print(terminal1)
    while True:
        terminal1.showMenu()
        menuPosition = input()
        terminal1.command(menuPosition)
