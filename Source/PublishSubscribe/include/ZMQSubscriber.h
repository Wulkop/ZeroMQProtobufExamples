#pragma once

#include <zmqpp.hpp>
#include <string>

class ZMQSubscriber
{
public:
	ZMQSubscriber();
	void connect(std::string hostname, std::string port);
	void startReceiveLoop();
private:
	zmqpp::context context;
	zmqpp::socket socket;
};