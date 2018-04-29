#include "include/ZMQPair.h"
#include<thread>


ZMQPair::ZMQPair():
context(),
socket(context, zmqpp::socket_type::pair)
{

}
void ZMQPair::connect(std::string hostname, std::string port)
{
	socket.connect("tcp://" + hostname + ":" + port);
}
void ZMQPair::bind(std::string port)
{
	socket.bind("tcp://*:" + port);
}
void ZMQPair::startReceiveLoop()
{
	while (true)
	{
		zmqpp::message msg;
		socket.receive(msg);
		std::cout << "Received: " << msg.get(0) << std::endl;
	}
}
void ZMQPair::sendMessage(std::string message)
{
	zmqpp::message msg;
	msg << message;
	socket.send(message);
}

void main()
{
	std::cout << "ZeroMq Pair2Pair example" << std::endl;
	std::cout << "1: Connect\n2: Bind" << std::endl;
	std::string input;
	std::cin >> input;
	ZMQPair zmqpair;
	if (input == "1")
	{
		std::cout << "ZeroMq Pair2Pair Socket example:" << std::endl;
		std::cout << "Please enter hostname" << std::endl;
		std::string hostname;
		std::string port;
		std::cin >> hostname;
		zmqpair.connect(hostname, "8080");
		std::cout << "Connecting to " << hostname << "with port 8080" << std::endl;
	}
	else if (input == "2")
	{
		zmqpair.bind("8080");
		std::cout << "Opening socket on port 8080" << std::endl;
	}
	else
	{
		return;
	}
	
	std::thread t1(std::bind(&ZMQPair::startReceiveLoop, &zmqpair));
	t1.detach();
	while (true)
	{
		std::string message;
		std::cout << "Please enter a message" << std::endl;
		std::getline(std::cin, message);
		zmqpair.sendMessage(message);
	}
}