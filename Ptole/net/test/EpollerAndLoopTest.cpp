#include<Ptole/net/Channel.h>
#include<Ptole/net/TcpServer.h>
#include<Ptole/net/InetAddress.h>
#include<Ptole/net/Loop.h>
using namespace Ptole::net;
int main() {
	Loop loop;
	InetAddress localAddress(8888);
	TcpServer tcpServer(localAddress,&loop);
	tcpServer.start();
	loop.loop();

	return 0;
}