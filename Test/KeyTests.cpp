#include <gtest\gtest.h>

#include "Key.h"
#include "Key.cpp"

TEST(IdSort, HighMedLow)
{
    int a = 99;
    int b = 52;
    int c = 10;
    SortIdsLowToHigh(a, b, c);

    EXPECT_EQ(10, a);
    EXPECT_EQ(52, b);
    EXPECT_EQ(99, c);
}

TEST(IdSort, HighLowMed)
{
    int a = 99;
    int b = 10;
    int c = 52;
    SortIdsLowToHigh(a, b, c);

    EXPECT_EQ(10, a);
    EXPECT_EQ(52, b);
    EXPECT_EQ(99, c);
}

TEST(IdSort, MedHighLow)
{
    int a = 52;
    int b = 99;
    int c = 10;
    SortIdsLowToHigh(a, b, c);

    EXPECT_EQ(10, a);
    EXPECT_EQ(52, b);
    EXPECT_EQ(99, c);
}

TEST(IdSort, MedLowHigh)
{
    int a = 52;
    int b = 10;
    int c = 99;
    SortIdsLowToHigh(a, b, c);

    EXPECT_EQ(10, a);
    EXPECT_EQ(52, b);
    EXPECT_EQ(99, c);
}

TEST(IdSort, LowHighMed)
{
    int a = 10;
    int b = 99;
    int c = 52;
    SortIdsLowToHigh(a, b, c);

    EXPECT_EQ(10, a);
    EXPECT_EQ(52, b);
    EXPECT_EQ(99, c);
}

TEST(IdSort, LowMedHigh)
{
    int a = 10;
    int b = 52;
    int c = 99;
    SortIdsLowToHigh(a, b, c);

    EXPECT_EQ(10, a);
    EXPECT_EQ(52, b);
    EXPECT_EQ(99, c);
}

TEST(KeyTest, CalculateKey4Ids)
{
    int id1 = 10;
    int id2 = 107;
    int id3 = 93;
    int id4 = 77;
    
    unsigned long key = CalculateTeamKey(id1, id2, id3, id4);

    unsigned long expected = 77093107010;

    EXPECT_EQ(expected, key);
}

TEST(KeyTest, CalculateKey3Ids)
{
    int id1 = 146;
    int id2 = 45;
    int id3 = 87;

    unsigned long key = CalculateTeamKey(id1, id2, id3);

    EXPECT_EQ(87045146, key);
}

TEST(KeyTest, CalculateKey2Ids)
{
    int id1 = 65;
    int id2 = 122;

    unsigned long key = CalculateTeamKey(id1, id2);

    EXPECT_EQ(122065, key);
}

TEST(KeyTest, ExtractId)
{
    int id1 = -1;
    int id2 = -1;

    unsigned long key = 122065;
    ExtractTwoManIds(key, id1, id2);

    EXPECT_EQ(65, id1);
    EXPECT_EQ(122, id2);
}