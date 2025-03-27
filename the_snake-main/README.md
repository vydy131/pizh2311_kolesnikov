# 🐍 Snake Game


## Управление

- **⬆️ Вверх** – движение вверх
- **⬇️ Вниз** – движение вниз
- **⬅️ Влево** – движение влево
- **➡️ Вправо** – движение вправо
- **ESC** – выход из игры

---

## 🛠 Интерфейсы классов

В проекте реализованы три основных класса: `GameObject`, `Apple` и `Snake`.

### **1. GameObject** (базовый класс)
```python
class GameObject:
    def __init__(self, position: tuple[int, int], body_color: tuple[int, int, int]):
        pass
    def draw(self):
        pass
```
#### **Атрибуты:**
- `position` – позиция объекта на игровом поле.
- `body_color` – цвет объекта.

#### **Методы:**
- `draw()` – отрисовывает объект на экране.

---

### **2. Apple** (наследуется от `GameObject`)
```python
class Apple(GameObject):
    def __init__(self):
        pass
    def randomize_position(self):
        pass
```
#### **Атрибуты:**
- `position` – случайная позиция яблока.
- `body_color` – красный цвет `RGB(255, 0, 0)`.

#### **Методы:**
- `randomize_position()` – устанавливает яблоко в случайное место.
- `draw()` – отрисовывает яблоко на экране (унаследован от `GameObject`).

---

### **3. Snake** (наследуется от `GameObject`)
```python
class Snake(GameObject):
    def __init__(self):
        pass
    def update(self, apple: Apple):
        pass
    def handle_keys(self):
        pass
    def reset(self):
        pass
```
#### **Атрибуты:**
- `positions` – список координат змейки.
- `direction` – текущее направление.
- `next_direction` – следующее направление.
- `body_color` – зелёный цвет `RGB(0, 255, 0)`.

#### **Методы:**
- `update(apple)` – обновляет положение змейки, проверяет столкновения.
- `handle_keys()` – обрабатывает нажатия клавиш.
- `reset()` – сбрасывает змейку в начальное состояние.
- `draw()` – отрисовывает змейку на экране.