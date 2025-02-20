import random


class Warrior:
    def __init__(self, name: str):
        self.name = name
        self.health = 100

    def take_damage(self, damage: int):
        self.health = max(0, self.health - damage)

    def is_alive(self) -> bool:
        return self.health > 0


class Battle:
    def __init__(self, warrior1: Warrior, warrior2: Warrior):
        self.warrior1 = warrior1
        self.warrior2 = warrior2

    def fight(self):
        while self.warrior1.is_alive() and self.warrior2.is_alive():
            attacker, defender = random.sample([self.warrior1, self.warrior2], 2)
            defender.take_damage(20)
            print(f"{attacker.name} атаковал {defender.name}, у {defender.name} осталось {defender.health} здоровья.")

        winner = self.warrior1 if self.warrior1.is_alive() else self.warrior2
        print(f"{winner.name} одержал победу!")


if __name__ == "__main__":
    warrior1 = Warrior("Воин 1")
    warrior2 = Warrior("Воин 2")
    battle = Battle(warrior1, warrior2)
    battle.fight()
