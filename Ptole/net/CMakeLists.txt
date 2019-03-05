SET(NET_SRCS 
	InetAddress.cpp
	SocketUtil.cpp
	Socket.cpp
	Channel.cpp
	TcpServer.cpp
	Channel.cpp
	Loop.cpp
	Epoller.cpp
	Buffer.cpp
	Connection.cpp
)

add_library(Ptole_net ${NET_SRCS})
add_subdirectory(test)