#include "singleton.hpp"

#include <iostream>
#include <thread>

using namespace std;

int main()
{
    std::cout << "START...\n";
    
    std::thread thd{[]
        {
            Singleton::instance().do_something();
        }};

    Singleton& singleObject = Singleton::instance();
    singleObject.do_something();

    thd.join();
}
