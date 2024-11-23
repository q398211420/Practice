#include <iostream>
#include "DataStructure.h"
#include <gtest/gtest.h>
using PathMatrix2D = bool[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
using ShortPathTable1D = int[MAX_VERTEX_NUM];
using PathMatrix3D = bool[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
using ShortPathTable2D = int[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/*迪杰斯特拉求单源最短路径算法*/  // 体现了贪心思想，动态规划
void ShortestPath_DIJ(GraphMatrix G, int v0, PathMatrix2D& P, ShortPathTable1D& D)
{
    bool final[G.vexnum] = {};  //初始全为false;
    for (size_t v = 0; v < G.vexnum; v++) {
        D[v] = G.arcs[v0][v];
        if (D[v] < INFINITY) {
            P[v][v0] = true;
            P[v][v] = true;
        }
    }
    D[v0] = 0;
    final[v0] = true;
    for (size_t i = 1; i < G.vexnum; i++) {
        int min = INFINITY;
        int v = -1;
        for (size_t w = 0; w < G.vexnum; w++) {
            if (!final[w] && D[w] < min) {
                v = w;
                min = D[w];
            }
        }
        final[v] = true;
        for (size_t w = 0; w < G.vexnum; w++) {
            //这里有个坑，《数据结构》书上没有G.arcs[v][w] != INFINITY这个判断。。实际上，必须要有，否则会溢出，因为INFINITY = INT_MAX
            int newDis = 0;
            bool overFlow = __builtin_add_overflow(min, G.arcs[v][w], &newDis);
            if (!final[w] && !overFlow && newDis < D[w]) {
                D[w] = min + G.arcs[v][w];
                memcpy(P[w], P[v], sizeof(bool) * G.vexnum);  // 把v0到w结点的路径更新为v0到v的路径
                P[w][w] = true;                               // v0到v的路径+v到w
            }
        }
    }
}

/*每一对顶点之间的最短路径*/
//可以用n次迪杰斯特拉算法，时间复杂度为O(n^3)
// 这里用弗洛伊德算法 有点像0-1背包问题的降维使用滚动数组的方式 时间复杂度也为O(n^3)
// 设求vi 到vj的最短路径，此时已经求得途经点序号，不超过k的最短路径，那么求不超过k+1的最短路径
// 则最短路径为 (vi 到vk+1) + (vk+1 到 vj) 和 此时的(vi到vj) 两者之间的较小者
void ShortestPath_FLOYD(GraphMatrix G, PathMatrix3D& P, ShortPathTable2D& D)
{
    for (size_t v = 0; v < G.vexnum; v++) {
        for (size_t w = 0; w < G.vexnum; w++) {
            D[v][w] = G.arcs[v][w];
            for (size_t u = 0; u < G.vexnum; u++) {
                P[v][w][u] = false;
            }
            if (D[v][w] < INFINITY) {
                P[v][w][v] = true;
                P[v][w][w] = true;
            }
        }
    }
    for (size_t u = 0; u < G.vexnum; u++) {
        for (size_t v = 0; v < G.vexnum; v++) {
            for (size_t w = 0; w < G.vexnum; w++) {
                int newDis{0};
                bool overFlow = __builtin_add_overflow(D[v][u], D[u][w], &newDis);
                if (!overFlow && newDis < D[v][w]) {
                    D[v][w] = newDis;
                    for (size_t i = 0; i < G.vexnum; i++) {
                        P[v][w][i] = P[v][u][i] || P[u][w][i];  // 可考虑用bitset去除循环
                    }
                }
            }
        }
    }
}

TEST(Algorithms, ShortestPath_DIJ)
{
    GraphMatrix G;
    G.vexnum = 6;
    G.arcnum = 8;
    G.kind = GraphKind::DN;
    G.vexs[0] = "v0";
    G.vexs[1] = "v1";
    G.vexs[2] = "v2";
    G.vexs[3] = "v3";
    G.vexs[4] = "v4";
    G.vexs[5] = "v5";
    G.arcs[0][2] = 10;
    G.arcs[0][4] = 30;
    G.arcs[0][5] = 100;
    G.arcs[1][2] = 5;
    G.arcs[2][3] = 50;
    G.arcs[3][5] = 10;
    G.arcs[4][3] = 20;
    G.arcs[4][5] = 60;
    PathMatrix2D P = {};
    ShortPathTable1D D;
    ShortestPath_DIJ(G, 0, P, D);
    for (size_t i = 0; i < G.vexnum; i++) {
        if (D[i] == INFINITY) {
            std::cout << G.vexs[i] << " INFINITY" << std::endl;
        }
        else {
            std::cout << G.vexs[i] << " " << D[i] << " (";
            for (size_t j = 0; j < G.vexnum; j++) {
                if (P[i][j] == true) {
                    std::cout << G.vexs[j] << " ";
                }
            }
            std::cout << ")" << std::endl;
        }
    }
}
TEST(Algorithms, ShortestPath_FLOYD)
{
    GraphMatrix G;
    G.vexnum = 6;
    G.arcnum = 8;
    G.kind = GraphKind::DN;
    G.vexs[0] = "v0";
    G.vexs[1] = "v1";
    G.vexs[2] = "v2";
    G.vexs[3] = "v3";
    G.vexs[4] = "v4";
    G.vexs[5] = "v5";
    G.arcs[0][2] = 10;
    G.arcs[0][4] = 30;
    G.arcs[0][5] = 100;
    G.arcs[1][2] = 5;
    G.arcs[2][3] = 50;
    G.arcs[3][5] = 10;
    G.arcs[4][3] = 20;
    G.arcs[4][5] = 60;
    PathMatrix3D P = {};
    ShortPathTable2D D;
    ShortestPath_FLOYD(G, P, D);
    for (size_t i = 0; i < G.vexnum; i++) {
        for (size_t j = 0; j < G.vexnum; j++) {
            if (i == j)
                continue;
            if (D[i][j] == INFINITY) {
                std::cout << G.vexs[i] << "," << G.vexs[j] << " INFINITY" << std::endl;
            }
            else {
                std::cout << G.vexs[i] << "," << G.vexs[j] << " " << D[i][j] << " (";
                for (size_t k = 0; k < G.vexnum; k++) {
                    if (P[i][j][k] == true) {
                        std::cout << G.vexs[k] << " ";
                    }
                }
                std::cout << ")" << std::endl;
            }
        }
    }
}
