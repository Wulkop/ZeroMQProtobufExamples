#include "include/ZMQProtobufServer.h"

ZMQProtobufServer::ZMQProtobufServer() :
	context(),
	socket(context, zmqpp::socket_type::pub)
{

}
void ZMQProtobufServer::bind(std::string port)
{
	socket.bind("tcp://*:" + port);
}
void ZMQProtobufServer::sendMessage(std::string message)
{
	zmqpp::message msg;
	msg << message;
	socket.send(message);
}

void constructPerson(tutorial::Person * person)
{
	std::string name;
	std::string email;
	std::cout << "Please enter the persons name" << std::endl;
	std::getline(std::cin, name);
	std::cout << "Please enter the persons email address" << std::endl;
	std::getline(std::cin, email);
	person->set_name(name);
	person->set_email(email);
	std::string choice;
	do
	{
		std::cout << "Do you want to add a phone number (Y/N)" << std::endl;
		std::getline(std::cin, choice);
		if (choice != "Y" && choice != "y")
		{
			break;
		}
		tutorial::Person_PhoneNumber * phone = person->add_phones();
		std::cout << "Which kind of number is ist?\n1.)Home\n2.)Work\n3.)Mobile" << std::endl;
		std::string photeTypeChoice;
		std::getline(std::cin, photeTypeChoice);
		if (photeTypeChoice == "1")
		{
			phone->set_type(tutorial::Person_PhoneType::Person_PhoneType_HOME);
		}
		else if (photeTypeChoice == "2")
		{
			phone->set_type(tutorial::Person_PhoneType::Person_PhoneType_WORK);
		}
		else if (photeTypeChoice == "3")
		{
			phone->set_type(tutorial::Person_PhoneType::Person_PhoneType_MOBILE);
		}
		std::cout << "Enter phone number" << std::endl;
		std::string phoneNumber;
		std::getline(std::cin, phoneNumber);
		phone->set_number(phoneNumber);

	} while (choice == "Y" || choice == "y");
	
}
int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	std::cout << "ZeroMq Protobuf Server Example:" << std::endl;
	ZMQProtobufServer server;
	server.bind("8080");
	std::cout << "Opening socket on port 8080" << std::endl;

	tutorial::AddressBook * book = new tutorial::AddressBook();
	while (true)
	{
		tutorial::Person * newPerson = book->add_people();
		constructPerson(newPerson);
		bool initialized = book->IsInitialized();
		book->PrintDebugString();
		std::string message = book->SerializeAsString();
		server.sendMessage(message);
	}
	return 0;
}
