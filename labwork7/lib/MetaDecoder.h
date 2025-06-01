#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>
#include <optional>
#include <map>
#include <stdexcept>

// Принцип SRP
// Отдельная функция для вычисления размера
uint32_t calculateFrameSize(const std::array<uint8_t, 4>& data);

// Базовый класс для хранения данных (SRP)
struct MetadataBlock {
    std::string identifier;
    uint32_t blockSize;
    uint16_t settings;
    std::vector<uint8_t> content;

    MetadataBlock(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct);
    virtual ~MetadataBlock() = default;
};

// Интерфейсы для ISP
class ITextContent {
public:
    virtual std::string getText() const = 0;
    virtual ~ITextContent() = default;
};

class IUrlContent {
public:
    virtual std::string getUrl() const = 0;
    virtual ~IUrlContent() = default;
};

class ICommentContent {
public:
    virtual std::string getLanguage() const = 0;
    virtual std::string getComment() const = 0;
    virtual ~ICommentContent() = default;
};

// Специализированные классы (ISP)
struct TextMetadata : MetadataBlock, ITextContent {
    TextMetadata(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct);
    std::string getText() const override;
};

struct WebLink : MetadataBlock, IUrlContent {
    WebLink(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct);
    std::string getUrl() const override;
};

struct UserComment : MetadataBlock, ICommentContent {
    UserComment(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct);
    std::string getLanguage() const override;
    std::string getComment() const override;
};

struct GenericBlock : MetadataBlock {
    using MetadataBlock::MetadataBlock;
};

// Принцип OCP
// Фабричный интерфейс
class BlockFactory {
public:
    virtual std::unique_ptr<MetadataBlock> create(
        const std::string& id,
        uint32_t size,
        uint16_t flags,
        const std::vector<uint8_t>& data
    ) = 0;
    virtual ~BlockFactory() = default;
};

// Реестр фабрик (OCP)
class BlockFactoryRegistry {
public:
    static void registerFactory(const std::string& id, std::unique_ptr<BlockFactory> factory);
    static std::unique_ptr<MetadataBlock> createBlock(
        const std::string& id,
        uint32_t size,
        uint16_t flags,
        const std::vector<uint8_t>& data
    );
private:
    static std::map<std::string, std::unique_ptr<BlockFactory>> factories;
};

// Принцип DIP
// Интерфейс обработчика
class IBlockProcessor {
public:
    virtual void processBlock(
        const std::string& id,
        uint32_t size,
        uint16_t flags,
        const std::vector<uint8_t>& data
    ) = 0;
    virtual ~IBlockProcessor() = default;
};

// Конкретная реализация процессора (DIP)
class BlockProcessor : public IBlockProcessor {
public:
    void processBlock(
        const std::string& id,
        uint32_t size,
        uint16_t flags,
        const std::vector<uint8_t>& data
    ) override;
};

// Принцип SRP
// Отдельный класс для отображения
class MetadataDisplay {
public:
    static void display(const MetadataBlock& block);
    static void displayText(const ITextContent& textBlock, const std::string& id);
    static void displayUrl(const IUrlContent& urlBlock, const std::string& id);
    static void displayComment(const ICommentContent& commentBlock, const std::string& id);
};

// Структура для сырых данных (SRP)
struct RawBlock {
    std::string id;
    uint32_t size;
    uint16_t flags;
    std::vector<uint8_t> data;
};

// Функции чтения данных (SRP)
std::optional<RawBlock> readNextBlock(std::ifstream& file, uint32_t& processed, uint32_t totalSize);
void parseMetadataBlocks(std::ifstream& file, uint32_t totalSize, IBlockProcessor& processor);

// Инициализация фабрик (OCP)
void initializeFactories();