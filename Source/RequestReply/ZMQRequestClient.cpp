#include "include/ZMQRequestClient.h"

ZMQRequestClient::ZMQRequestClient():
	context(),
	socket(context, zmqpp::socket_type::dealer)
{

}
void ZMQRequestClient::connect(std::string hostname, std::string port)
{
	socket.connect("tcp://" + hostname + ":" + port);
}
void ZMQRequestClient::setIdentity(std::string identity)
{
	this->identity = identity;
	socket.set(zmqpp::socket_option::identity, identity);
}
void ZMQRequestClient::sendRequest(std::string request)
{
	zmqpp::message requestMsg;
	requestMsg << identity;
	requestMsg << request;
	//requestMsg << request;
	socket.send(requestMsg);
	zmqpp::message reply;
	socket.receive(reply);
	std::cout <<"Answer from server: "<< reply.get(0) << std::endl;
}

void main()
{
	ZMQRequestClient requestClient;

	std::cout << "ZeroMq Subscriber Socket example:" << std::endl;
	std::cout << "Please enter hostname" << std::endl;
	std::string hostname;
	std::string port;
	std::getline(std::cin, hostname);
	requestClient.connect(hostname, "8080");
	std::cout << "Connecting to " << hostname << " with port 8080" << std::endl;
	std::cout << "Enter nickname" << std::endl;
	std::string identity;
	std::getline(std::cin, identity);
	requestClient.setIdentity(identity);

	while (true)
	{
		std::cout << "Please enter message to reverse by server" << std::endl;
		std::string request;
		std::getline(std::cin, request);
		requestClient.sendRequest(request);
	}
}
