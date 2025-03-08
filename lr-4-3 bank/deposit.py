# Программирование на языке высокого уровня (Python).
# Задание №3.
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com


class FixedDeposit:
    """Абстрактный класс - срочный вклад."""

    def __init__(self, name, interest_rate, period_limit, sum_limit):
        """Инициализировать атрибуты класса."""
        self.name = name
        self._interest_rate = interest_rate
        self._period_limit = period_limit
        self._sum_limit = sum_limit

        self._check_self()

    def __str__(self):
        """Вернуть строкое представление депозита."""
        return (f"Name: {self.name}\n"
                f"Currency: {self.currency}\n"
                f"Interest Rate: {self._interest_rate}%\n"
                f"Term (months): {self._period_limit}\n"
                f"Amount Range: {self._sum_limit}")

    @property
    def currency(self):
        return "руб."

    def _check_self(self):
        """Проверить, что данные депозита являются допустимыми."""
        assert 0 < self._interest_rate <= 100, "Invalid interest rate!"
        assert 1 <= self._period_limit[0] < self._period_limit[1], "Invalid period limit!"
        assert 0 < self._sum_limit[0] <= self._sum_limit[1], "Invalid sum limit!"

    def _check_user_params(self, initial_sum, period):
        """Проверить, что данные депозита соответствуют его ограничениям."""
        is_sum_ok = self._sum_limit[0] <= initial_sum < self._sum_limit[1]
        is_period_ok = self._period_limit[0] <= period < self._period_limit[1]
        assert is_sum_ok and is_period_ok, "Deposit conditions are not met!"

    def get_profit(self, initial_sum, period):
        """Вернуть прибыль по вкладу вклада клиента."""
        self._check_user_params(initial_sum, period)
        return initial_sum * self._interest_rate / 100 * period / 12

    def get_sum(self, initial_sum, period):
        """Вернуть сумму вклада клиента после начисления прибыли."""
        return initial_sum + self.get_profit(initial_sum, period)


class BonusDeposit(FixedDeposit):
    """Срочный вклад с получением бонуса к концу срока вклада."""

    def __init__(self, name, interest_rate, period_limit, sum_limit, bonus):
        """Инициализировать атрибуты класса."""
        self._bonus = bonus  # Определяем _bonus перед super().__init__
        super().__init__(name, interest_rate, period_limit, sum_limit)

    def __str__(self):
        """Вернуть строкое представление депозита."""
        return (super().__str__() +
                f"\nBonus (%): {self._bonus['percent']}%\n"
                f"Bonus (min. sum): {self._bonus['sum']}")

    def _check_self(self):
        """Проверить, что данные депозита являются допустимыми."""
        super()._check_self()
        assert 0 <= self._bonus["percent"] <= 100, "Invalid bonus percent!"
        assert self._bonus["sum"] > 0, "Invalid bonus sum!"

    def get_profit(self, initial_sum, period):
        """Вернуть прибыль по вкладу клиента с учетом бонуса."""
        profit = super().get_profit(initial_sum, period)
        if initial_sum > self._bonus["sum"]:
            profit += profit * self._bonus["percent"] / 100
        return profit


class CompoundDeposit(FixedDeposit):
    """Cрочный вклад c ежемесячной капитализацией процентов."""

    def __str__(self):
        """Вернуть строкое представление депозита."""
        return super().__str__() + "\nCapitalization: Yes"

    def get_profit(self, initial_sum, period):
        """Вернуть прибыль по вкладу клиента."""
        self._check_user_params(initial_sum, period)
        return initial_sum * (1 + self._interest_rate / 100 / 12) ** period - initial_sum


deposits_data = dict(interest_rate=5, period_limit=(6, 18), sum_limit=(1000, 100000))

# Список имеющихся депозитов
deposits = [
    FixedDeposit("Save", **deposits_data),
    BonusDeposit("Bonus", **deposits_data, bonus=dict(percent=5, sum=2000)),
    CompoundDeposit("With Capitalization", **deposits_data)
]
