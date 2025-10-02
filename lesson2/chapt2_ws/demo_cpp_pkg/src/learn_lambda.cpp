#include <iostream>
#include <algorithm>

int main()
{
    auto add = [](int a, int b) -> int
    { return a + b; };
    int sum = add(2, 3);
    auto print_sum = [&sum]() -> void
    {
        std::cout << "The sum is: " << sum << std::endl;
    };
    print_sum();
    return 0;
}