#include "include/ZMQProtobufClient.h"

ZMQProtobufClient::ZMQProtobufClient() :
	context(),
	socket(context, zmqpp::socket_type::sub)
{

}
void ZMQProtobufClient::connect(std::string hostname, std::string port)
{
	socket.subscribe("");
	socket.connect("tcp://" + hostname + ":" + port);
}
void ZMQProtobufClient::startReceiveLoop()
{
	while (true)
	{
		zmqpp::message msg;
		socket.receive(msg);
		std::string messageString = msg.get(0);
		printDeserializedAddressbook(messageString);
	}
}
void ZMQProtobufClient::printDeserializedAddressbook(std::string message)
{
	tutorial::AddressBook book;
	book.ParseFromString(message);
	book.PrintDebugString();
}

void main()
{
	ZMQProtobufClient client;

	std::cout << "ZeroMq Protobuf Client Example:" << std::endl;
	std::cout << "Please enter hostname" << std::endl;
	std::string hostname;
	std::string port;
	std::cin >> hostname;
	client.connect(hostname, "8080");
	std::cout << "Connecting to " << hostname << " with port 8080" << std::endl;

	std::thread t1(std::bind(&ZMQProtobufClient::startReceiveLoop, &client));
	t1.join();
}