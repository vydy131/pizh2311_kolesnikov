# Программирование на языке высокого уровня (Python).
# Задание №2.
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com


class Pizza:
    def __init__(self, title, dough, sauce, filling, price):
        self.title = title
        self.dough = dough
        self.sauce = sauce
        self.filling = filling
        self.price = price

    def __str__(self):
        return (f"Pizza: {self.title} | Цена: {self.price:.2f} р.\n"
                f"   Тесто: {self.dough} Соус: {self.sauce}\n"
                f"   Начинка: {', '.join(self.filling)}")

    def prepare(self):
        print(f"Начинаю готовить пиццу {self.title}")
        print(f"  - замешиваю {self.dough} dough...")
        print(f"  - добавляю sauce: {self.sauce}...")
        print(f"  - и, конечно: {', '.join(self.filling)}...")

    def bake(self):
        print("Выпекаю пиццу... Готово!")

    def slice(self):
        print("Нарезаю на аппетитные кусочки...")

    def pack(self):
        print("Упаковываю в фирменную упаковку и готово!")


class PizzaPeperoni(Pizza):
    def __init__(self):
        super().__init__("Пепперони", "тонкое", "томатный", ["пепперони", "сыр моцарелла"], 350.00)


class PizzaBBQ(Pizza):
    def __init__(self):
        super().__init__("Барбекю", "тонкое", "барбекю", ["бекон", "ветчина", "зелень", "сыр моцарелла"], 450.00)


class PizzaSea(Pizza):
    def __init__(self):
        super().__init__("Дары моря", "пышное", "тар-тар", ["кальмары", "креветки", "мидии", "сыр моцарелла"], 550.00)