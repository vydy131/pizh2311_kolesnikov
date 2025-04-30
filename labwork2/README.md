# Лабораторная работа 2

## API
```cpp
struct uint2022_t {
    static const int CAPACITY = 70;
    uint32_t data[CAPACITY] = {0};
};

uint2022_t from_uint( uint32_t );
uint2022_t from_string( char* );

uint2022_t operator + ( uint2022_t, uint2022_t);
uint2022_t operator - ( uint2022_t, uint2022_t);
uint2022_t operator * ( uint2022_t, uint2022_t);
uint2022_t operator / ( uint2022_t, uint2022_t);
uint2022_t operator % ( uint2022_t, uint2022_t);

bool operator == ( uint2022_t, uint2022_t);
bool operator != ( uint2022_t, uint2022_t);

std::ostream& operator << ( std::ostream&, uint2022_t );
```

## Задача

  Реализовать пользовательский тип для целого беззнакового числа
фиксированной длины **uint2022_t**. Размер получившегося типа не должен превышать 300 байт.

  Для вышеуказанного типа требуется реализовать следующий набор функций и операторов

     1. Конвертация из типа uint32_t
     2. Конвертация из строки
     3. Сложение
     4. Вычитание
     5. Умножение
     6. Вывод числа в консоль
     7. Сравнение (== и !=)
     8. Деление*
     
