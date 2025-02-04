#pragma once
#include "RemoteService.h"

class HelloService : public RemoteService
{
public:
	std::string sayHello(const std::string& name) override
	{
		return "Hello " + name;
	}
};