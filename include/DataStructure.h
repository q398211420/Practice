#include <array>
#include <vector>
#include <memory>
#include <queue>
#include <stack>
static constexpr int MAX_VERTEX_NUM = 20;
using InfoType = int;
using VertexType = std::string;

enum class GraphKind { DG, DN, UDG, UDN };  //有向图，有向网，无向图，无向网
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

struct Graph
{
    AdjList vertices;
    int vexnum, arcnum;
    GraphKind kind;
};