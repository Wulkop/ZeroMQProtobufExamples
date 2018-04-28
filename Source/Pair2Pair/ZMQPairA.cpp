#include "include/ZMQPair.h"
#include<thread>


ZMQPairA::ZMQPairA():
context(),
socket(context, zmqpp::socket_type::pair)
{

}
void ZMQPairA::connect(std::string hostname, std::string port)
{
	socket.connect("tcp://" + hostname + ":" + port);
}
void ZMQPairA::bind(std::string port)
{
	socket.bind("tcp://*:" + port);
}
void ZMQPairA::startReceiveLoop()
{
	while (true)
	{
		zmqpp::message msg;
		socket.receive(msg);
		std::cout << "Received: " << msg.get(0) << std::endl;
	}
}
void ZMQPairA::sendMessage(std::string message)
{
	zmqpp::message msg;
	msg << message;
	socket.send(message);
}

void main()
{
	std::cout << "1: Connect\n2: Bind" << std::endl;
	std::string input;
	std::cin >> input;
	ZMQPairA zmqpair;
	if (input == "1")
	{
		std::cout << "Please enter hostname" << std::endl;
		std::string hostname;
		std::string port;
		std::cin >> hostname;
		std::cout << "Please enter port" << std::endl;
		std::cin >> port;
		zmqpair.connect(hostname, port);
	}
	else if (input == "2")
	{
		std::string port;
		std::cout << "Please enter port" << std::endl;
		std::cin >> port;
		zmqpair.bind(port);
	}
	
	std::thread t1(std::bind(&ZMQPairA::startReceiveLoop, &zmqpair));
	t1.detach();
	while (true)
	{
		std::string message;
		std::cout << "Please enter a message" << std::endl;
		std::cin >> message;
		zmqpair.sendMessage(message);
	}
}