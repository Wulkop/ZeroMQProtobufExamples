#include "include/ZMQPublisher.h"
ZMQPublisher::ZMQPublisher():
	context(),
	socket(context, zmqpp::socket_type::pub)
{

}
void ZMQPublisher::bind(std::string port)
{
	socket.bind("tcp://*:" + port);
}
void ZMQPublisher::sendMessage(std::string message)
{
	zmqpp::message msg;
	msg << message;
	socket.send(message);
}

void main()
{
	std::cout << "ZeroMq Publisher Socket example:" << std::endl;
	ZMQPublisher publisher;
	publisher.bind("8080");
	std::cout << "Opening socket on port 8080" << std::endl;
	while (true)
	{
		std::string message;
		std::cout << "Please enter a message" << std::endl;
		std::getline(std::cin, message);
		publisher.sendMessage(message);
	}
}