#include <iostream>
#include <functional>

int print_with_free_fun(const std::string &str)
{
    std::cout<<"print_with_free_fun:" << str << std::endl;
    return 0;
}

class TestClass
{
public:
    TestClass() = default;
    ~TestClass() = default;
    void print_with_member_fun(const std::string &str)
    {
        std::cout<<"print_with_member_fun:" << str << std::endl;
    }
};

int main()
{
    TestClass test_obj;
    auto print_with_lambda_fun = [](const std::string &str) -> void
    {
        std::cout<<"print_with_lambda_fun:" << str << std::endl;
    };

    std::function<void(const std::string &)>prt1=print_with_free_fun;;
    std::function<void(const std::string &)>prt2=print_with_lambda_fun;
    std::function<void(const std::string &)>prt3=std::bind(&TestClass::print_with_member_fun,&test_obj,std::placeholders::_1);

    prt1("Hello, world!");
    prt2("Hello, world!");
    prt3("Hello, world!");
    return 0;
}