# Программирование на языке высокого уровня (Python).
# Задание №2.
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com


import time


class Order:
    orderCount = 0

    def __init__(self):
        self.pizzaOrderList = []
        Order.orderCount += 1
        self.orderId = Order.orderCount

    def __str__(self):
        result = [f"Order №{self.orderId}"]
        for i, pizza in enumerate(self.pizzaOrderList, start=1):
            result.append(f"{i}. {pizza}")
        result.append(f"Сумма заказа: {self.amount():.2f} р.")
        return '\n'.join(result)

    def add(self, pizza):
        self.pizzaOrderList.append(pizza)
        print(f"Pizza {pizza.title} добавлена!")

    def amount(self):
        return sum(pizza.price for pizza in self.pizzaOrderList)

    def execute(self):
        print("Order поступил на выполнение...")
        for i, pizza in enumerate(self.pizzaOrderList, start=1):
            print(f"{i}. {pizza.title}")
            time.sleep(1)
            pizza.prepare()
            time.sleep(1)
            pizza.bake()
            time.sleep(1)
            pizza.slice()
            time.sleep(1)
            pizza.pack()
            print()
        print(f"Order №{self.orderId} готов! Приятного аппетита!")
