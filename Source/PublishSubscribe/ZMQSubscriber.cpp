#include "include/ZMQSubscriber.h"

ZMQSubscriber::ZMQSubscriber() :
	context(),
	socket(context, zmqpp::socket_type::sub)
{

}
void ZMQSubscriber::connect(std::string hostname, std::string port)
{
	socket.subscribe("");
	socket.connect("tcp://" + hostname + ":" + port);
}
void ZMQSubscriber::startReceiveLoop()
{
	while (true)
	{
		zmqpp::message msg;
		socket.receive(msg);
		std::cout << "Received: " << msg.get(0) << std::endl;
	}
}

void main()
{
	ZMQSubscriber subscriber;

	std::cout << "ZeroMq Subscriber Socket Example:" << std::endl;
	std::cout << "Please enter hostname" << std::endl;
	std::string hostname;
	std::string port;
	std::cin >> hostname;
	subscriber.connect(hostname, "8080");
	std::cout << "Connecting to " << hostname << " with port 8080" << std::endl;

	std::thread t1(std::bind(&ZMQSubscriber::startReceiveLoop, &subscriber));
	t1.join();
}