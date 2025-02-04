#pragma once
#include "RemoteService.h"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class RemoteSkeleton
{
	boost::asio::io_context io_context;
	tcp::acceptor acceptor;
	RemoteService& service;

	void handleRequest(tcp::socket& socket)
	{
		char data[1024];
		boost::system::error_code error;
		size_t length = socket.read_some(boost::asio::buffer(data));
		if (!error)
		{
			std::string request(data, length);
			std::string response;
			if (request.rfind("sayHello", 0) == 0)
			{
				std::string name = request.substr(9);
				response = service.sayHello(name);
			}
			else
			{
				response = "Unknown request";
			}
			boost::asio::write(socket, boost::asio::buffer(response),error);
		}
	}
public:
	RemoteSkeleton(RemoteService& service, int port) : acceptor{io_context, tcp::endpoint{tcp::v4(), static_cast<boost::asio::ip::port_type>(port)}},
	                                                   service{service}
	{}
	void start()
	{
		std::cout << "Server started....\n";
		while (true)
		{
			tcp::socket socket{io_context};
			acceptor.accept(socket);
			handleRequest(socket); // 동기 호출
			//std::thread{ [this, &socket] { handleRequest(socket); } }.detach();//비동기 호출
		}
	}
};