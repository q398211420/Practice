#include <iostream>
#include <stack>
#include <map>
#include <gtest/gtest.h>
std::map<std::stack<int>*, std::string> g_name;
void Recursion(int n, std::stack<int>& A, std::stack<int>& B, std::stack<int>& C)
{
    if (n == 1) {
        auto e = A.top();
        A.pop();
        std::cout << "move " << e << " from " << g_name[&A] << " to " << g_name[&C] << std::endl;
        C.push(e);
        return;
    }
    Recursion(n - 1, A, C, B);
    auto e = A.top();
    A.pop();
    std::cout << "move " << e << " from " << g_name[&A] << " to " << g_name[&C] << std::endl;
    C.push(e);

    Recursion(n - 1, B, A, C);
}
TEST(Algorithms, TowerOfHanoi)
{
    std::stack<int> A;
    std::stack<int> B;
    std::stack<int> C;
    g_name[&A] = "A";
    g_name[&B] = "B";
    g_name[&C] = "C";
    A.push(3);
    A.push(2);
    A.push(1);
    auto n = A.size();
    Recursion(n, A, B, C);
    std::cout << "A: " << std::endl;
    while (!A.empty()) {
        auto e = A.top();
        A.pop();
        std::cout << e << " " << std::endl;
    }
    std::cout << "B: " << std::endl;
    while (!B.empty()) {
        auto e = B.top();
        B.pop();
        std::cout << e << " " << std::endl;
    }
    std::cout << "C: " << std::endl;
    while (!C.empty()) {
        auto e = C.top();
        C.pop();
        std::cout << e << " " << std::endl;
    }
   
}