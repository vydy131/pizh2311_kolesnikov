#include <gtest/gtest.h>
#include "../lib/Sandpile.h"
TEST(SandpileTest, LoadFromFileWorks) {
    Sandpile s(5, 5);
    EXPECT_NO_THROW(s.loadFromFile("/home/vydy131/CLionProjects/pizh2311_kolesnikov/labwork3/input/test_input.tsv"));
}
TEST(SandpileTest, RunDoesNotCrash) {
    Sandpile s(5, 5);
    s.loadFromFile("/home/vydy131/CLionProjects/pizh2311_kolesnikov/labwork3/input/test_input.tsv");
    EXPECT_NO_THROW(s.run());
}
TEST(SandpileTest, FieldIsNonEmptyAfterRun) {
    Sandpile s(5, 5);
    s.loadFromFile("/home/vydy131/CLionProjects/pizh2311_kolesnikov/labwork3/input/test_input.tsv");
    s.run();
    const auto& field = s.getField();
    bool hasGrains = false;
    for (const auto& row : field)
        for (auto cell : row)
            if (cell > 0)
                hasGrains = true;
    EXPECT_TRUE(hasGrains);
}
TEST(SandpileTest, FieldSizeIsCorrect) {
    Sandpile s(7, 3);
    s.loadFromFile("/home/vydy131/CLionProjects/pizh2311_kolesnikov/labwork3/input/test_input.tsv");
    s.run();
    const auto& field = s.getField();
    EXPECT_EQ(field.size(), 3);
    for (const auto& row : field)
        EXPECT_EQ(row.size(), 7);
}
TEST(SandpileTest, StableAfterRun) {
    Sandpile s(10, 10);
    s.loadFromFile("/home/vydy131/CLionProjects/pizh2311_kolesnikov/labwork3/input/test_input.tsv");
    s.run();
    const auto& field = s.getField();
    for (const auto& row : field)
        for (auto cell : row)
            EXPECT_LT(cell, 4);
}