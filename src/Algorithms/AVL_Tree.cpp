/*平衡二叉树的算法练习*/
#include "DataStructure.h"
#include "gtest/gtest.h"
#include <iomanip>
inline constexpr int LH = 1;
inline constexpr int EH = 0;
inline constexpr int RH = -1;

void L_Rotate(AVLTree& T)
{
    auto rc = T->rchild;
    T->rchild = rc->lchild;
    rc->lchild = T;
    T = rc;
}

void R_Rotate(AVLTree& T)
{
    auto lc = T->lchild;
    T->lchild = lc->rchild;
    lc->rchild = T;
    T = lc;
}

void LeftBalance(AVLTree& T)
// 对以指针T所指结点为根的二叉树做做平衡旋转处理，本算法结束时，指针T指向新的根结点
{
    AVLTree lc = T->lchild;
    switch (lc->bf) {
        case LH:
            T->bf = EH;
            lc->bf = EH;
            R_Rotate(T);
            break;
        case RH: {
            auto rd = lc->rchild;
            switch (rd->bf) {
                case LH:
                    T->bf = RH;
                    lc->bf = EH;
                    break;
                case EH:
                    T->bf = lc->bf = EH;
                    break;
                case RH:
                    T->bf = EH;
                    lc->bf = LH;
                    break;
                default:
                    break;
            }
            rd->bf = EH;
            L_Rotate(T->lchild);
            R_Rotate(T);
            break;
        }
        default:
            break;
    }
}

void RightBalance(AVLTree& T)
// 对以指针T所指结点为根的二叉树做做平衡旋转处理，本算法结束时，指针T指向新的根结点
{
    AVLTree rc = T->rchild;
    switch (rc->bf) {
        case RH:
            T->bf = EH;
            rc->bf = EH;
            L_Rotate(T);
            break;
        case LH: {
            auto ld = rc->lchild;
            switch (ld->bf) {
                case LH:
                    T->bf = EH;
                    rc->bf = RH;
                    break;
                case EH:
                    T->bf = rc->bf = EH;
                    break;
                case RH:
                    T->bf = LH;
                    rc->bf = EH;
                    break;
                default:
                    break;
            }
            ld->bf = EH;
            R_Rotate(T->rchild);
            L_Rotate(T);
            break;
        }
        default:
            break;
    }
}

void DestroyAVL(AVLTree& T)
{
    if (T) {
        DestroyAVL(T->lchild);
        DestroyAVL(T->rchild);
        delete T;
        T = nullptr;
    }
}

auto InsertAVL(AVLTree& T, int e, bool& taller) -> int
// 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素
// 为e的新结点，并返回1，否则返回0.若因插入而使二叉排序树失去平衡，则作平衡
// 旋转处理，布尔变量taller反映T长高与否
{
    if (!T) {
        T = new AVLNode;
        T->data = e;
        T->lchild = T->rchild = nullptr;
        T->bf = EH;
        taller = true;
    }
    else {
        if (e == T->data) {
            taller = false;
            return 0;
        }
        if (e < T->data) {
            if (!InsertAVL(T->lchild, e, taller))
                return 0;
            if (taller) {
                switch (T->bf) {
                    case LH:
                        LeftBalance(T);
                        taller = false;
                        break;
                    case EH:
                        T->bf = LH;
                        taller = true;
                        break;
                    case RH:
                        T->bf = EH;
                        taller = false;
                        break;
                    default:
                        break;
                }
            }
        }
        else {
            if (!InsertAVL(T->rchild, e, taller))
                return 0;
            if (taller) {
                switch (T->bf) {
                    case LH:
                        T->bf = EH;
                        taller = false;
                        break;
                    case EH:
                        T->bf = RH;
                        taller = true;
                        break;
                    case RH:
                        RightBalance(T);
                        taller = false;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return 1;
}

auto AVL_Search(AVLTree T, int e) -> AVLTree
{
    while (T && T->data != e) {
        if (T->data > e) {
            T = T->lchild;
        }
        else {
            T = T->rchild;
        }
    }
    return T;
}

auto AVL_Delete() -> AVLTree
{
    /*
    1. 用二叉排序树的方法对结点w执行删除操作
    2. 若导致了不平衡，从结点w开始向上回溯，找到第一个不平衡的结点z(即最小不平衡子树);
        y为结点z高度最高的孩子结点
        x是结点y高度最高的孩子结点
    3. 然后对以z为根的子树进行平衡调整，其中x，y和z可能的位置有四种情况:
        y是z的左孩子，x是y的左孩子(LL,右单旋转)
        y是z的左孩子，x是y的右孩子(LR,先左后右双旋转)
        y是z的右孩子，x是y的右孩子(RR,左单旋转)
        y是z的右孩子，x是y的左孩子(RL,先右后左双旋转)
    
    这四种情况与插入操作的调整方式一样。不同之处在于，插入操作仅需要对以z为根的子树进行平衡调整;而删除操作就不一样，先对
    以z为根的子树进行平衡调整，如果调整后子树的高度减1，则可能需要对z的祖先结点进行平衡调整，甚至回溯到根结点(导致树高减1)
    */
    return nullptr;
}

// 递归打印二叉树
void printTree(AVLTree root, int depth = 0, bool isRight = false)
{
    if (!root)
        return;

    // 递归打印右子树
    printTree(root->rchild, depth + 1, true);

    // 打印当前节点
    if (depth > 0) {
        std::cout << std::setw(4 * depth - 2) << "" << (isRight ? "┌── " : "└── ");
    }
    std::cout << root->data << std::endl;

    // 递归打印左子树
    printTree(root->lchild, depth + 1, false);
}

TEST(Algorithms, AVL_Tree)
{
    AVLTree T = nullptr;
    bool taller = false;
    InsertAVL(T, 1, taller);
    InsertAVL(T, 2, taller);
    InsertAVL(T, 3, taller);
    InsertAVL(T, 4, taller);
    InsertAVL(T, 5, taller);
    InsertAVL(T, 6, taller);
    InsertAVL(T, 7, taller);
    InsertAVL(T, 8, taller);
    InsertAVL(T, 9, taller);
    printTree(T);
    DestroyAVL(T);
}