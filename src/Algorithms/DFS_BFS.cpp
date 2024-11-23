#include <iostream>
#include "DataStructure.h"
#include <gtest/gtest.h>

/*
                  v1
                 /  \  
                v2   \
               /  \   \
              v4   v5  \          
               \   /   v3
                v8    /  \          
                     v6---v7             
                   
                                           
*/
namespace Recursive {
    void DFS(const GraphList& G, int v, std::vector<bool>& visited)
    {
        auto vertex = G.vertices[v];
        std::cout << vertex.data << std::endl;
        visited[v] = true;
        for (auto next = vertex.firstarc; next != nullptr;
             next = next->nextarc) {
            v = next->adjvex;
            if (!visited[v]) {
                DFS(G, v, visited);
            }
        }
    }
    void DFSTraverse(const GraphList& G)
    {
        std::cout << "DFSTraverse with recursive:" << std::endl;

        std::vector<bool> visited(G.vexnum, false);
        for (int v = 0; v < G.vexnum; v++) {
            if (!visited[v]) {
                DFS(G, v, visited);
            }
        }
    }
}  // namespace Recursive

namespace NoRecursive {
    //这里和数据结构P170的算法不大一样。 
    //书上是先访问，再把访问后的元素加入队列，队列只起记录顺序的作用，实际在队列外已经访问完成了。
    //此处是把要访问的元素置为true后加入队列，队列里的元素代表要访问的元素，等待访问。
    //不管哪种方法，一定要先设置true再加入队列，不然可能出现同一个顶点被加入两次的情况（由于visited状态未更新）
    void BFSTraverse(const GraphList& G)
    {
        std::cout << "BFSTraverse without recursive:" << std::endl;
        std::vector<bool> visited(G.vexnum, false);
        std::queue<int> q;
        for (int i = 0; i < G.vexnum; i++) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    std::cout << G.vertices[v].data << std::endl;
                    for (auto next = G.vertices[v].firstarc; next != nullptr;
                         next = next->nextarc) {
                        if (!visited[next->adjvex]) {
                            visited[next->adjvex] = true;
                            q.push(next->adjvex);
                        }
                    }
                }
            }
        }
    }

    //同BFS,栈里的元素代表要访问的元素，先置为ture再入栈。
    //置为true的元素不代表已经访问完成，只代表元素已经入栈。
    //实际访问完成在出栈时刻。
    void DFSTraverse(const GraphList& G)
    {
        std::cout << "DFSTraverse without recursive:" << std::endl;
        std::vector<bool> visited(G.vexnum, false);
        std::stack<int> s;
        std::stack<int> r;
        for (int i = 0; i < G.vexnum; i++) {
            if (!visited[i]) {
                visited[i] = true;
                s.push(i);
                while (!s.empty()) {
                    int v = s.top();
                    s.pop();
                    std::cout << G.vertices[v].data << std::endl;
                    for (auto next = G.vertices[v].firstarc; next != nullptr;
                         next = next->nextarc) {
                        if (!visited[next->adjvex]) {
                            r.push(next->adjvex);
                            visited[next->adjvex] = true;
                        }
                    }  //由于是单链表，用了辅助栈r，目的是确保相邻顶点访问顺序与递归算法一致。
                       //如果按照1234入栈，出栈顺序则为4321，此处加了一个辅助栈，还原顺序。
                       //若AdjList为双向链表，直接rend - > rbegin.
                    while (!r.empty()) {
                        s.push(r.top());
                        r.pop();
                    }
                }
            }
        }
    }

}  // namespace NoRecursive

GraphList GeneTestGraph()
{
    GraphList::AdjList al;
    al[0].data = "v1";
    al[1].data = "v2";
    al[2].data = "v3";
    al[3].data = "v4";
    al[4].data = "v5";
    al[5].data = "v6";
    al[6].data = "v7";
    al[7].data = "v8";

    auto a12 = std::make_shared<GraphList::ArcNode>();
    auto a13 = std::make_shared<GraphList::ArcNode>();
    auto a21 = std::make_shared<GraphList::ArcNode>();
    auto a24 = std::make_shared<GraphList::ArcNode>();
    auto a25 = std::make_shared<GraphList::ArcNode>();
    auto a31 = std::make_shared<GraphList::ArcNode>();
    auto a36 = std::make_shared<GraphList::ArcNode>();
    auto a37 = std::make_shared<GraphList::ArcNode>();
    auto a42 = std::make_shared<GraphList::ArcNode>();
    auto a48 = std::make_shared<GraphList::ArcNode>();
    auto a52 = std::make_shared<GraphList::ArcNode>();
    auto a58 = std::make_shared<GraphList::ArcNode>();
    auto a63 = std::make_shared<GraphList::ArcNode>();
    auto a67 = std::make_shared<GraphList::ArcNode>();
    auto a73 = std::make_shared<GraphList::ArcNode>();
    auto a76 = std::make_shared<GraphList::ArcNode>();
    auto a84 = std::make_shared<GraphList::ArcNode>();
    auto a85 = std::make_shared<GraphList::ArcNode>();

    al[0].firstarc = (a12);
    al[1].firstarc = (a21);
    al[2].firstarc = (a31);
    al[3].firstarc = (a42);
    al[4].firstarc = (a52);
    al[5].firstarc = (a63);
    al[6].firstarc = (a73);
    al[7].firstarc = (a84);

    a12->adjvex = 1;
    a13->adjvex = 2;
    a12->nextarc = (a13);
    a13->nextarc = nullptr;

    a21->adjvex = 0;
    a21->nextarc = (a24);
    a24->adjvex = 3;
    a24->nextarc = (a25);
    a25->adjvex = 4;
    a25->nextarc = nullptr;

    a31->adjvex = 0;
    a31->nextarc = (a36);
    a36->adjvex = 5;
    a36->nextarc = (a37);
    a37->adjvex = 6;
    a37->nextarc = nullptr;

    a42->adjvex = 3;
    a42->nextarc = (a48);
    a48->adjvex = 7;
    a48->nextarc = nullptr;

    a52->adjvex = 4;
    a52->nextarc = (a58);
    a58->adjvex = 7;
    a58->nextarc = nullptr;

    a63->adjvex = 2;
    a63->nextarc = (a67);
    a67->adjvex = 6;
    a67->nextarc = nullptr;

    a73->adjvex = 2;
    a73->nextarc = (a76);
    a76->adjvex = 5;
    a76->nextarc = nullptr;

    a84->adjvex = 3;
    a84->nextarc = (a85);
    a85->adjvex = 4;
    a85->nextarc = nullptr;

    GraphList G;
    G.vertices = (al);
    G.vexnum = 8;
    G.arcnum = 18;
    G.kind = GraphKind::UDG;

    return G;
}

TEST(Algorithms, DFS_BFS)
{
    auto G = GeneTestGraph();
    //Recursive::DFSTraverse(G);
    //NoRecursive::BFSTraverse(G);
    NoRecursive::DFSTraverse(G);
}