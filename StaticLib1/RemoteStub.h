#pragma once
#include "RemoteService.h"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class RemoteStub : public RemoteService
{
	tcp::socket socket;
	tcp::endpoint endpoint;
	boost::asio::io_context io_context;
	std::mutex mtx;
public:
	RemoteStub(const std::string& host, int port) : socket{ io_context }, endpoint{ boost::asio::ip::make_address(host), static_cast<boost::asio::ip::port_type>(port) }
	{
		std::lock_guard<std::mutex> lock(mtx);
		boost::system::error_code error;
		socket.connect(endpoint, error);
		if (error)
		{
			throw std::runtime_error("Connection failed");
		}
	}
	std::string sayHello(const std::string& name) override
	{
		std::lock_guard<std::mutex> lock(mtx);
		std::string request = "Say Hello " + name;
		boost::asio::write(socket, boost::asio::buffer(request));

		char reply[1024];
		size_t reply_length = socket.read_some(boost::asio::buffer(reply));
		return std::basic_string<char>(reply, reply_length);
	}

};
	
