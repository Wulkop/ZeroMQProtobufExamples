#pragma once
#include <zmqpp.hpp>
#include <string>
#include "addressbook.pb.h"

class ZMQProtobufServer
{
public:
	ZMQProtobufServer();
	void bind(std::string port);
	void sendMessage(std::string message);
private:
	zmqpp::context context;
	zmqpp::socket socket;
};