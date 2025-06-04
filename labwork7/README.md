# Лабораторная работа 7

## Применение принципов SOLID


### Далее работа до SOLID

#### SRP
```c++
// Было: Классы совмещали хранение данных и вывод
void MetadataBlock::display() const;

// Стало: Отдельный класс для отображения
class MetadataDisplay {
public:
    static void display(const MetadataBlock& block);
    static void displayText(...);
    // ...
};
```
#### OCP
```c++
// Было: Жесткая фабрика с switch-case
std::unique_ptr<MetadataBlock> createMetadataBlock(...) {
    switch(id[0]) { ... }
}

// Стало: Реестр фабрик
class BlockFactoryRegistry {
    static void registerFactory(...);
    static std::unique_ptr<MetadataBlock> createBlock(...);
};
```
#### LSP
```c++
// Было: Проверка в методе display()
void UserComment::display() const {
    if (content.size() < 4) { ... }
}

// Стало: Гарантия корректного состояния в конструкторе
UserComment::UserComment(...) {
    if (content.size() < 4) 
        throw std::invalid_argument(...);
}
```
#### ISP
```c++
// Было: Один базовый класс для всех
struct MetadataBlock { ... };

// Стало: Специализированные интерфейсы
class ITextContent {
    virtual std::string getText() const = 0;
};

class TextMetadata : MetadataBlock, ITextContent { ... };
```
#### DIP
```c++
// Было: Прямая зависимость от реализации
void parseMetadataBlocks(std::ifstream& file, uint32_t totalSize);

// Стало: Зависимость от абстракции
class IBlockProcessor {
    virtual void processBlock(...) = 0;
};

void parseMetadataBlocks(..., IBlockProcessor& processor);
```

#### MetaDecoder — класс для чтения ID3v2-тегов в MP3 с гибкой архитектурой (базовый класс + специализированные подклассы).

## Тесты проверяют:
 - Парсинг бинарных данных
 - Фабрику тегов (TextMetadata, WebLink и др.)
 - Обработку ошибок (битые заголовки, неполные данные)
 - Интеграцию с файлами (через TempFileFixture)

## UML-диаграмма классов
![UML](puml.png)

