#include<Ptole/net/Channel.h>
#include<Ptole/net/TcpServer.h>
#include<Ptole/net/InetAddress.h>
using namespace Ptole::net;
int main() {
	InetAddress localAddress(8888);
	TcpServer tcpServer(localAddress);
	tcpServer.start();
}