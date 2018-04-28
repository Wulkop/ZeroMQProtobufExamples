CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)


SET(ZMQ_STATIC_DEFINITION "-DZMQ_STATIC -std=c++11")
ADD_DEFINITIONS(${ZMQ_STATIC_DEFINITION})
SET(PAIR2PAIR_DIR "Pair2Pair")
SET(PUBLISH_SUBSCRIBE_DIR "PublishSubscribe")
SET(REQUEST_REPLY_DIR "RequestReply")
SET(ZMQ_PROTOBUF_DIR "ZMQProtobuf")


message(${ZMQPP_INCLUDE_DIR})
INCLUDE_DIRECTORIES(
		${ZeroMQ_INCLUDE_DIR}
		${PROTOBUF_INCLUDE_DIR}
		${PROTOBUF_MESSAGE_INCLUDE_DIR}
		${ZMQPP_INCLUDE_DIR}
	)
	
#=============================Executable===============================
ADD_EXECUTABLE(Pair2PairClient
		${PAIR2PAIR_DIR}/ZMQPair.cpp
	)
TARGET_LINK_LIBRARIES(Pair2PairClient
		libzmq-static
		zmqpp-static
	)
ADD_DEPENDENCIES(Pair2PairClient
		libzmq-static
		zmqpp-static
	)

#=============================Executable===============================
ADD_EXECUTABLE(PublishSubscribePublisher
		${PUBLISH_SUBSCRIBE_DIR}/ZMQPublisher.cpp
	)
TARGET_LINK_LIBRARIES(PublishSubscribePublisher
		libzmq-static
		zmqpp-static
	)
ADD_DEPENDENCIES(PublishSubscribePublisher
		libzmq-static
		zmqpp-static
	)
#=============================Executable===============================
ADD_EXECUTABLE(PublishSubscribeSubscriber
		${PUBLISH_SUBSCRIBE_DIR}/ZMQSubscriber.cpp
	)
TARGET_LINK_LIBRARIES(PublishSubscribeSubscriber
		libzmq-static
		zmqpp-static
	)
ADD_DEPENDENCIES(PublishSubscribeSubscriber
		libzmq-static
		zmqpp-static
	)
#=============================Executable===============================
ADD_EXECUTABLE(RequestReplyServer
		${REQUEST_REPLY_DIR}/ZMQReplyServer.cpp
	)
TARGET_LINK_LIBRARIES(RequestReplyServer
		libzmq-static
		zmqpp-static
	)
ADD_DEPENDENCIES(RequestReplyServer
		libzmq-static
		zmqpp-static
	)
#=============================Executable===============================
ADD_EXECUTABLE(RequestReplyClient
		${REQUEST_REPLY_DIR}/ZMQRequestClient.cpp
	)
TARGET_LINK_LIBRARIES(RequestReplyClient
		libzmq-static
		zmqpp-static
	)
ADD_DEPENDENCIES(RequestReplyClient
		libzmq-static
		zmqpp-static
	)
#=============================Executable===============================
ADD_EXECUTABLE(ZmqProtobufClient
		${ZMQ_PROTOBUF_DIR}/ZMQProtobufClient.cpp
		${PROTOBUF_MESSAGE_INCLUDE_DIR}/addressbook.pb.cc
	)
TARGET_LINK_LIBRARIES(ZmqProtobufClient
		libzmq-static
		zmqpp-static
		libprotobuf
		libprotoc
	)
ADD_DEPENDENCIES(ZmqProtobufClient
		libzmq-static
		zmqpp-static
		libprotobuf
		libprotoc
	)
#=============================Executable===============================
ADD_EXECUTABLE(ZmqProtobufServer
		${ZMQ_PROTOBUF_DIR}/ZMQProtobufServer.cpp
		${PROTOBUF_MESSAGE_INCLUDE_DIR}/addressbook.pb.cc
	)
TARGET_LINK_LIBRARIES(ZmqProtobufServer
		libzmq-static
		zmqpp-static
		libprotobuf
		libprotoc
	)
ADD_DEPENDENCIES(ZmqProtobufServer
		libzmq-static
		zmqpp-static
		libprotobuf
		libprotoc
	)
	
#============================Plattform dependent stuff=================

IF(WIN32)
TARGET_LINK_LIBRARIES(ZmqProtobufServer
		ws2_32
		iphlpapi
	)
TARGET_LINK_LIBRARIES(ZmqProtobufClient
		ws2_32
		iphlpapi
	)
ENDIF()
IF(UNIX)
	TARGET_LINK_LIBRARIES(ZmqProtobufServer
		pthread
	)
	TARGET_LINK_LIBRARIES(ZmqProtobufClient
		pthread
	)
endif()
