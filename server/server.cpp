// server.cpp
#include "../StaticLib1/HelloService.h"
#include "../StaticLib1/RemoteSkeleton.h"
#include "../StaticLib1/framework.h"

int main() {
	global_mutex.lock();
    HelloService service;
    RemoteSkeleton skeleton(service, 12345);
	global_mutex.unlock();
    skeleton.start();
    return 0;
}