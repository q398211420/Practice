#include <iostream>
auto Recursion(int n) -> int
{
   if(n<=1){
       return 1;
   }
   if(n<=2){
       return 2;
   }
   return Recursion(n - 1) + Recursion(n - 2);
}
auto main(int argc, const char** argv) -> int
{
    int n;
    std::cin >> n;
    std::cout << Recursion(n) << std::endl;
    return 0;
}