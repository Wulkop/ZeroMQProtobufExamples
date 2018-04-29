#include "include/ZMQReplyServer.h"

ZMQReplyServer::ZMQReplyServer():
	context(),
	socket(context, zmqpp::socket_type::router)
{

}
void ZMQReplyServer::bind(std::string port)
{
	socket.bind("tcp://*:" + port);
}
void ZMQReplyServer::startReceiveLoop()
{
	while (true)
	{
		zmqpp::message request;
		socket.receive(request);
		std::string identity = request.get(1);
		std::string text = request.get(2);
		std::cout << "Processing request from " << identity << " : " << text << std::endl;
		std::cout << "Reversing string " << text << std::endl;
		std::reverse(text.begin(), text.end());
		zmqpp::message reply;
		reply << request.get(0);
		reply << text;
		socket.send(reply);
	}
}

int main()
{
	std::cout << "ZeroMq Reply Server Example" << std::endl;
	ZMQReplyServer replyServer;

	replyServer.bind("8080");
	std::cout << "Opening socket on port 8080" << std::endl;

	std::thread t1(std::bind(&ZMQReplyServer::startReceiveLoop, &replyServer));
	t1.join();
	return 0;
}
