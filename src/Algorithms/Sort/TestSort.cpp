#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <filesystem>
#include "Sort.h"

const char* inputFilePath = "../../../src/Algorithms/Sort/test_data_input";
const char* outputFilePath = "../../../src/Algorithms/Sort/test_data_out";

// 顺便练习一下设计模式之策略模式

class SortStrategy {
public:
    virtual void MySort(std::array<int, 1000>& nums, std::function<bool(int, int)> predicate = std::less<>{}) = 0;
    virtual ~SortStrategy() = default;
};

class UseInsertSort : public SortStrategy {
public:
    void MySort(std::array<int, 1000>& nums, std::function<bool(int, int)> predicate) override
    {
        InsertSort(nums.begin(), nums.end(), predicate);
    }
};

class UseBInsertSort : public SortStrategy {
public:
    void MySort(std::array<int, 1000>& nums, std::function<bool(int, int)> predicate) override
    {
        BInsertSort(nums.begin(), nums.end(), predicate);
    }
};

class UseBubbleSort : public SortStrategy {
public:
    void MySort(std::array<int, 1000>& nums, std::function<bool(int, int)> predicate) override
    {
        BubbleSort(nums.begin(), nums.end(), predicate);
    }
};

class UseQuickSort : public SortStrategy {
public:
    void MySort(std::array<int, 1000>& nums, std::function<bool(int, int)> predicate) override
    {
        QuickSort(nums.begin(), nums.end(), predicate);
    }
};

class UseHeapSort : public SortStrategy {
public:
    void MySort(std::array<int, 1000>& nums, std::function<bool(int, int)> predicate) override
    {
        HeapSort(nums.begin(), nums.end(), predicate);
    }
};

class UseMergeSort : public SortStrategy {
public:
    void MySort(std::array<int, 1000>& nums, std::function<bool(int, int)> predicate) override
    {
        MergeSort(nums.begin(), nums.end(), predicate);
    }
};

class SortedArray {
public:
    SortedArray(std::unique_ptr<SortStrategy> s)
    {
        m_strategy = std::move(s);
    }
    SortedArray() = default;
    void SetData(const std::array<int, 1000>& data)
    {
        m_data = data;
    }
    void Sort()
    {
        if (m_isAscending)
            m_strategy->MySort(m_data);
        else
            m_strategy->MySort(m_data, std::greater<>{});
    }
    void SetAscend()
    {
        m_isAscending = true;
    }
    void SetDescend()
    {
        m_isAscending = false;
    }
    const auto& GetData() const
    {
        return m_data;
    }

private:
    std::array<int, 1000> m_data;
    std::unique_ptr<SortStrategy> m_strategy{nullptr};
    bool m_isAscending{true};
};

class SortTest : public ::testing::Test {
public:
    static auto GetOriginData() -> std::array<int, 1000> const
    {
        return m_originData;
    }
    static auto GetAscendData() -> std::array<int, 1000> const
    {
        return m_ascending;
    }
    static auto GetDescendData() -> std::array<int, 1000> const
    {
        return m_descending;
    }

protected:
    static std::array<int, 1000> m_originData;
    static std::array<int, 1000> m_ascending;
    static std::array<int, 1000> m_descending;
    static bool m_isDataLoaded;
    SortTest()
    {
        if (!m_isDataLoaded) {
            std::ifstream file;

            file.open(inputFilePath);
            if (!file.is_open()) {
                std::cerr << "找不到排序输入数据!" << std::endl;
                return;
            }
            int value;
            int i = 0;
            while (file >> value) {
                m_originData[i] = value;
                i++;
            }
            file.close();
            file.open(outputFilePath);
            if (!file.is_open()) {
                std::cerr << "找不到排序输出数据!" << std::endl;
                return;
            }
            i = 0;
            while (file >> value) {
                m_ascending[i] = value;
                i++;
            }

            m_descending = m_ascending;
            std::reverse(m_descending.begin(), m_descending.end());
            m_isDataLoaded = true;
        }
    }
};
bool SortTest::m_isDataLoaded = false;
std::array<int, 1000> SortTest::m_originData;
std::array<int, 1000> SortTest::m_ascending;
std::array<int, 1000> SortTest::m_descending;
TEST_F(SortTest, InsertSort)
{
    auto v = SortTest::GetOriginData();
    SortedArray test(std::make_unique<UseInsertSort>());
    test.SetData(v);

    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetAscendData());

    test.SetDescend();
    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetDescendData());
}

TEST_F(SortTest, BInsertSort)
{
    auto v = SortTest::GetOriginData();
    SortedArray test(std::make_unique<UseBInsertSort>());
    test.SetData(v);

    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetAscendData());

    test.SetDescend();
    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetDescendData());
}

TEST_F(SortTest, BubbleSort)
{
    auto v = SortTest::GetOriginData();
    SortedArray test(std::make_unique<UseBubbleSort>());
    test.SetData(v);

    test.Sort();
    ASSERT_EQ(test.GetData(), SortTest::GetAscendData());

    test.SetDescend();
    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetDescendData());
}
TEST_F(SortTest, HeapSort)
{
    auto v = SortTest::GetOriginData();
    SortedArray test(std::make_unique<UseHeapSort>());
    test.SetData(v);

    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetAscendData());

    test.SetDescend();
    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetDescendData());
}
TEST_F(SortTest, MergeSort)
{
    auto v = SortTest::GetOriginData();
    SortedArray test(std::make_unique<UseMergeSort>());
    test.SetData(v);
    
    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetAscendData());

    test.SetDescend();
    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetDescendData());
}
TEST_F(SortTest, QuickSort)
{
    auto v = SortTest::GetOriginData();
    SortedArray test(std::make_unique<UseQuickSort>());
    test.SetData(v);

    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetAscendData());

    test.SetDescend();
    test.Sort();
    EXPECT_EQ(test.GetData(), SortTest::GetDescendData());
}
TEST_F(SortTest, RadixSort) {}
TEST_F(SortTest, SelectSort) {}
TEST_F(SortTest, ShellSort) {}