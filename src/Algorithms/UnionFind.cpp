#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <optional>
class UnionFind {
public:
    UnionFind(int n) : parent(n), unionSize(n, 1)
    {
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
        }
    }
    std::optional<int> Find(int x)
    {
        if (x < 0 || x >= parent.size()) {
            return std::nullopt;
        }
        // find root
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }

        // path compression
        while (parent[x] != x) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        return root;
    }

    std::optional<int> FindRecursive(int x)
    {
        if (x < 0 || x >= parent.size()) {
            return std::nullopt;
        }
        if (parent[x] != x) {
            parent[x] = *Find(x);
        }

        return parent[x];
    }
    void Unite(int a, int b)
    {
        if (a < 0 || b < 0 || a >= parent.size() || b >= parent.size()) {
            return;
        }
        int rootA = Find(a).value();
        int rootB = Find(b).value();
        if (rootA != rootB) {
            if (unionSize[rootA] < unionSize[rootB])
                std::swap(rootA, rootB);
            parent[rootB] = rootA;
            unionSize[rootA] += unionSize[rootB];
        }
    }
    bool IsConnected(int a, int b)
    {
        auto oa = Find(a);
        auto ob = Find(b);
        if (!(oa && ob))
            return false;
        return oa.value() == ob.value();
    }

private:
    std::vector<int> parent;
    std::vector<int> unionSize;
};

TEST(Algorithms, UnionFind_Find)
{
    UnionFind uf(10);

    uf.Unite(0, 9);
    uf.Unite(9, 2);

    EXPECT_TRUE(uf.Find(2).value() == uf.Find(0).value());
}
TEST(Algorithms, UnionFind_FindRecursive)
{
    UnionFind uf(10);

    uf.Unite(0, 9);
    uf.Unite(9, 2);

    EXPECT_TRUE(uf.FindRecursive(2).value() == uf.FindRecursive(0).value());
}
TEST(Algorithms, UnionFind_Unite)
{
    UnionFind uf(6);

    uf.Unite(0, 1);
    uf.Unite(1, 2);

    EXPECT_TRUE(uf.IsConnected(0, 2));

    UnionFind uf1(8);

    uf1.Unite(0, 1);
    uf1.Unite(2, 3);
    uf1.Unite(4, 5);
    uf1.Unite(6, 7);

    EXPECT_FALSE(uf1.IsConnected(0, 3));
    EXPECT_TRUE(uf1.IsConnected(4, 5));

    uf1.Unite(1, 2);
    EXPECT_TRUE(uf1.IsConnected(0, 3));
    EXPECT_FALSE(uf1.IsConnected(0, 4));

    UnionFind uf2(7);

    uf2.Unite(0, 1);
    uf2.Unite(1, 2);

    uf2.Unite(3, 4);

    uf2.Unite(5, 6);

    uf2.Unite(2, 3);
    uf2.Unite(4, 5);

    for (int i = 0; i < 7; ++i) {
        EXPECT_TRUE(uf2.IsConnected(0, i));
    }

    UnionFind uf3(5);

    uf3.Unite(0, 1);
    uf3.Unite(1, 2);

    uf3.Unite(0, 2);  // 已经属于同一个集合
    uf3.Unite(2, 0);  // 再来一次
    uf3.Unite(1, 1);  // 自己和自己合并

    EXPECT_TRUE(uf3.IsConnected(0, 2));
    EXPECT_FALSE(uf3.IsConnected(0, 3));
}
TEST(Algorithms, UnionFind_IsConnected)
{
    UnionFind uf(6);

    uf.Unite(5, 1);

    EXPECT_TRUE(uf.IsConnected(5, 1));
}