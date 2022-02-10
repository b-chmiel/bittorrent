#include <iostream>
#include <boost/asio.hpp>

int main()
{
        boost::asio::io_service service;

        auto work = []() {
            std::cout << "Hello, World!" << std::endl;
        };

        service.post(work);
        service.run();

        return 0;
}
