#pragma once
#include <zmqpp.hpp>
#include <string>
#include "addressbook.pb.h"

class ZMQProtobufClient
{
public:
	ZMQProtobufClient();
	void connect(std::string hostname, std::string port);
	void startReceiveLoop();
private:
	void printDeserializedAddressbook(std::string messge);
	zmqpp::context context;
	zmqpp::socket socket;
};