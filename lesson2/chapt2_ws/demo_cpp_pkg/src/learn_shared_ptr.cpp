#include <iostream>
#include <memory>

int main()
{
    auto p1 = std::make_shared<std::string>("Hello, world!");
    std::cout << "p1的引用计数:" << p1.use_count() << ",指向内存地址：" << p1.get() << std::endl;

    auto p2 = p1;
    std::cout << "p2的引用计数:" << p2.use_count() << ",指向内存地址：" << p2.get() << std::endl;

    p1.reset();
    std::cout << "p1的引用计数:" << p1.use_count() << ",指向内存地址：" << p1.get() << std::endl;
    std::cout << "p2的引用计数:" << p2.use_count() << ",指向内存地址：" << p2.get() << std::endl;

    std::cout << "p2指向的字符串内容：" << p2->c_str() << std::endl; // 输出p2指向的字符串内容

    return 0;
}