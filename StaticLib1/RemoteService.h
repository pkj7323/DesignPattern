#pragma once
#include <string>

class RemoteService
{
public:
	virtual std::string sayHello(const std::string& name) = 0;
};