#include "MetaDecoder.h"
#include <algorithm>
#include <functional>

// Реализация реестра фабрик
std::map<std::string, std::unique_ptr<BlockFactory>> BlockFactoryRegistry::factories;

void BlockFactoryRegistry::registerFactory(
    const std::string& id,
    std::unique_ptr<BlockFactory> factory
) {
    factories[id] = std::move(factory);
}

std::unique_ptr<MetadataBlock> BlockFactoryRegistry::createBlock(
    const std::string& id,
    uint32_t size,
    uint16_t flags,
    const std::vector<uint8_t>& data
) {
    // Поиск по полному идентификатору
    if (auto it = factories.find(id); it != factories.end()) {
        return it->second->create(id, size, flags, data);
    }

    // Поиск по префиксу
    std::string prefix(1, id[0]);
    if (auto it = factories.find(prefix); it != factories.end()) {
        return it->second->create(id, size, flags, data);
    }

    return std::make_unique<GenericBlock>(id, size, flags, data);
}

class TextBlockFactory : public BlockFactory {
public:
    std::unique_ptr<MetadataBlock> create(
        const std::string& id,
        uint32_t size,
        uint16_t flags,
        const std::vector<uint8_t>& data
    ) override {
        return std::make_unique<TextMetadata>(id, size, flags, data);
    }
};

class WebBlockFactory : public BlockFactory {
public:
    std::unique_ptr<MetadataBlock> create(
    const std::string& id,
        uint32_t size,
        uint16_t flags,
        const std::vector<uint8_t>& data
    ) override {
        return std::make_unique<WebLink>(id, size, flags, data);
    }
};

class CommentBlockFactory : public BlockFactory {
public:
    std::unique_ptr<MetadataBlock> create(
    const std::string& id,
        uint32_t size,
        uint16_t flags,
        const std::vector<uint8_t>& data
    ) override {
        return std::make_unique<UserComment>(id, size, flags, data);
    }
};

void initializeFactories() {
    BlockFactoryRegistry::registerFactory("T", std::make_unique<TextBlockFactory>());
    BlockFactoryRegistry::registerFactory("W", std::make_unique<WebBlockFactory>());
    BlockFactoryRegistry::registerFactory("COMM", std::make_unique<CommentBlockFactory>());
}

// Реализация базового класса
MetadataBlock::MetadataBlock(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct)
    : identifier(id), blockSize(sz), settings(fl), content(ct) {}

// Реализация специализированных классов
TextMetadata::TextMetadata(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct)
    : MetadataBlock(id, sz, fl, ct) {}

std::string TextMetadata::getText() const {
    return content.empty() ? "" : std::string(content.begin() + 1, content.end());
}

WebLink::WebLink(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct)
    : MetadataBlock(id, sz, fl, ct) {}

std::string WebLink::getUrl() const {
    return std::string(content.begin(), content.end());
}

UserComment::UserComment(const std::string& id, uint32_t sz, uint16_t fl, const std::vector<uint8_t>& ct)
    : MetadataBlock(id, sz, fl, ct) {
    if (content.size() < 4) {
        throw std::invalid_argument("Invalid comment block size");
    }
}

std::string UserComment::getLanguage() const {
    return std::string(content.begin() + 1, content.begin() + 4);
}

std::string UserComment::getComment() const {
    auto textStart = std::find(content.begin() + 4, content.end(), 0);
    if (textStart == content.end()) {
        return "";
    }
    return std::string(textStart + 1, content.end());
}

// Реализация отображения
void MetadataDisplay::display(const MetadataBlock& block) {
    std::cout << block.identifier << " [" << block.blockSize << " bytes]";
}

void MetadataDisplay::displayText(const ITextContent& textBlock, const std::string& id) {
    std::cout << "[*] " << id << ": " << textBlock.getText();
}

void MetadataDisplay::displayUrl(const IUrlContent& urlBlock, const std::string& id) {
    std::cout << "[*] " << id << " (URL): " << urlBlock.getUrl();
}

void MetadataDisplay::displayComment(const ICommentContent& commentBlock, const std::string& id) {
    std::cout << "[*] " << id << " [" << commentBlock.getLanguage() << "]: "
              << commentBlock.getComment();
}

// Вспомогательные функции
uint32_t calculateFrameSize(const std::array<uint8_t, 4>& bytes) {
    return (bytes[0] << 21) | (bytes[1] << 14) | (bytes[2] << 7) | bytes[3];
}

std::optional<RawBlock> readNextBlock(std::ifstream& file, uint32_t& processed, uint32_t totalSize) {
    if (processed + 10 > totalSize) return std::nullopt;

    RawBlock block;
    block.id.resize(4);
    file.read(&block.id[0], 4);
    if (file.gcount() != 4) return std::nullopt;

    std::array<uint8_t, 4> sizeData{};
    file.read(reinterpret_cast<char*>(sizeData.data()), 4);
    block.size = calculateFrameSize(sizeData);

    file.read(reinterpret_cast<char*>(&block.flags), 2);
    if (file.gcount() != 2) return std::nullopt;

    if (block.size > totalSize - processed - 10) return std::nullopt;

    block.data.resize(block.size);
    file.read(reinterpret_cast<char*>(block.data.data()), block.size);
    if (file.gcount() != static_cast<int>(block.size)) return std::nullopt;

    processed += 10 + block.size;
    return block;
}

void parseMetadataBlocks(std::ifstream& file, uint32_t totalSize, IBlockProcessor& processor) {
    uint32_t processed = 0;

    // Инициализация фабрик
    initializeFactories();

    while (processed < totalSize) {
        auto rawBlock = readNextBlock(file, processed, totalSize);
        if (!rawBlock) break;

        processor.processBlock(
            rawBlock->id,
            rawBlock->size,
            rawBlock->flags,
            rawBlock->data
        );
    }
}

// Реализация метода BlockProcessor::processBlock
void BlockProcessor::processBlock(
    const std::string& id,
    uint32_t size,
    uint16_t flags,
    const std::vector<uint8_t>& data
) {
    auto block = BlockFactoryRegistry::createBlock(id, size, flags, data);
    if (!block) return;

    // Использование специализированных интерфейсов (ISP)
    if (auto textBlock = dynamic_cast<ITextContent*>(block.get())) {
        MetadataDisplay::displayText(*textBlock, id);
    }
    else if (auto urlBlock = dynamic_cast<IUrlContent*>(block.get())) {
        MetadataDisplay::displayUrl(*urlBlock, id);
    }
    else if (auto commentBlock = dynamic_cast<ICommentContent*>(block.get())) {
        MetadataDisplay::displayComment(*commentBlock, id);
    }
    else {
        MetadataDisplay::display(*block);
    }
    std::cout << '\n';
}