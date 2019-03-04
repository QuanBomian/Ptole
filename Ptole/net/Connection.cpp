#include<Ptole/net/Connection.h>
using namespace  Ptole::net;

Ptole::net::Connection::Connection(int sockfd, Loop * loop, InetAddress localAddress, InetAddress peerAddress):
socket_(new Socket(sockfd)),loop_(loop),localAddress_(localAddress),peerAddress_(peerAddress)
{
}
