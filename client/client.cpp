#include "../StaticLib1/RemoteStub.h"
#include "../StaticLib1/framework.h"

int main() {
    global_mutex.lock();
    RemoteStub stub("127.0.0.1", 12345);
	global_mutex.unlock();
    std::string response = stub.sayHello("Alice");
    std::cout << "Server response: " << response << std::endl;
    return 0;
}