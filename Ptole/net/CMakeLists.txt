SET(NET_SRCS 
	InetAddress.cpp
	SocketUtil.cpp
	Socket.cpp
	Channel.cpp
	TcpServer.cpp
)

add_library(Ptole_net ${NET_SRCS})
add_subdirectory(test)