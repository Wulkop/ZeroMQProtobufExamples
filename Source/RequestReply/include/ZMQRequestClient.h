#pragma once
#include <zmqpp.hpp>
#include <string>

class ZMQRequestClient
{
public:
	ZMQRequestClient();
	void setIdentity(std::string);
	void connect(std::string hostname, std::string port);
	void sendRequest(std::string message);
private:
	zmqpp::context context;
	zmqpp::socket socket;
	std::string identity;
};