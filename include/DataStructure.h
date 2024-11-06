#include <array>
#include <vector>
#include <memory>
#include <queue>
#include <stack>
static constexpr int MAX_VERTEX_NUM = 20;
static constexpr int INFINITY = INT_MAX;
using InfoType = int;
using VertexType = std::string;

enum class GraphKind { DG, DN, UDG, UDN };  //有向图，有向网，无向图，无向网
class GraphList {
public:
    struct ArcNode
    {
        int adjvex;
        std::shared_ptr<ArcNode> nextarc;
        InfoType* info{nullptr};
    };
    struct VNode
    {
        VertexType data;
        std::shared_ptr<ArcNode> firstarc;
    };

    using AdjList = std::array<VNode, MAX_VERTEX_NUM>;
    AdjList vertices;
    int vexnum, arcnum;
    GraphKind kind;
};  //图的邻接表表示法

class GraphMatrix {
public:
    GraphMatrix()
    {
        for (auto& row : arcs) {
            for (auto& e : row) {
                e = INFINITY;
            }
        }
    }
    using VRtype = int;
    // struct ArcCell
    // {
    //     VRtype adj;
    //     InfoType* info;
    // };

    GraphKind kind;
    VertexType vexs[MAX_VERTEX_NUM];
    VRtype arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;

};  //图的邻接矩阵表示法
