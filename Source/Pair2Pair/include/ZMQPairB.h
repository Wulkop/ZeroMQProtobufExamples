#pragma once
#include <zmqpp.hpp>
#include <string>

class ZMQPairA
{
public:
	ZMQPairA();
	void connect(std::string hostname, std::string port);
	void bind(std::string port);
	void startReceiveLoop();
	void sendMessage(std::string message);
private:
	zmqpp::context context;
	zmqpp::socket socket;
};