#pragma once
#include <zmqpp.hpp>
#include <string>
#include <algorithm>
class ZMQReplyServer
{
public:
	ZMQReplyServer();
	void bind(std::string port);
	void startReceiveLoop();
private:
	zmqpp::context context;
	zmqpp::socket socket;
};
