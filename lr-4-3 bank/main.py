# Программирование на языке высокого уровня (Python).
# Задание №3.
#
# Выполнил: Колесников ВГ
# Группа: ПИЖ 23 1 1
# E-mail: vydy131@gmail.com


from deposit import deposits

if __name__ == "__main__":
    print("Добро пожаловать в систему подбора вкладов!")

    while True:
        print("\n-----")
        print("Нажмите 1, чтобы подобрать вклад, или что угодно для выхода.")

        answer = input()
        if answer == "1":

            initial_sum = float(input("1/2: Введите начальную сумму вклада: "))
            period = int(input("2/2: Введите срок вклада (мес.): "))

            matched_deposits = []
            for deposit in deposits:
                try:
                    deposit._check_user_params(initial_sum, period)
                    matched_deposits.append(deposit)
                except AssertionError:
                    pass

            if matched_deposits:
                print("{0:18} | {1:13} | {2:13}".format(
                    "Вклад", "Прибыль", "Итоговая сумма"
                ))
                for deposit in matched_deposits:
                    print("{0:18} | {1:8,.2f} {3:4} | {2:8,.2f} {3:4}".format(
                          deposit.name,
                          deposit.get_profit(initial_sum, period),
                          deposit.get_sum(initial_sum, period),
                          deposit.currency))
            else:
                print("К сожалению, нет подходящих Вам вкладов.")

        else:
            break

    print("\nСпасибо, что воспользовались терминалом банка! До встречи!")


# -----
# Нажмите 1, чтобы подобрать вклад, или что угодно для выхода.
# 1
# 1/2: Введите начальную сумму вклада: 2000
# 2/2: Введите срок вклада (мес.): 7
# Вклад              | Прибыль       | Итоговая сумма
# Save               |    58.33 руб. | 2,058.33 руб.
# Bonus              |    58.33 руб. | 2,058.33 руб.
# With Capitalization |    59.07 руб. | 2,059.07 руб.
#
# -----
# Нажмите 1, чтобы подобрать вклад, или что угодно для выхода.