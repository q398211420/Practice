/*迪杰斯特拉求单源最短路径算法*/
#include <iostream>
#include "DataStructure.h"
#include <gtest/gtest.h>
using PathMatrix = bool[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
using ShortPathTable = int[MAX_VERTEX_NUM];
void ShortestPath_DIJ(GraphMatrix G, int v0, PathMatrix& P, ShortPathTable& D)
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
            if (!final[w] && G.arcs[v][w] != INFINITY && (min + G.arcs[v][w]) < D[w]) {
                D[w] = min + G.arcs[v][w];
                memcpy(P[w], P[v], sizeof(bool) * G.vexnum);  // 把v0到w结点的路径更新为v0到v的路径
                P[w][w] = true;                               // v0到v的路径+v到w
            }
        }
    }
}

TEST(ShortestPath, Test1)
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
    PathMatrix P = {};
    ShortPathTable D;
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