#pragma once
#include<zmqpp.hpp>
#include<string>
class ZMQPublisher
{
public:
	ZMQPublisher();
	void bind(std::string port);
	void sendMessage(std::string message);
private:
	zmqpp::context context;
	zmqpp::socket socket;
};