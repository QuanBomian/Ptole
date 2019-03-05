
#include<Ptole/net/Buffer.h>
using namespace  Ptole::net;
const char* Buffer::peek() const
{
	return buffer_.c_str();
}

int Buffer::readableBytes() const
{
	return buffer_.size();
}

void Buffer::append(const std::string& data)
{
	buffer_.append(data);
}

void Buffer::retrieve(size_t len)
{
	buffer_ = buffer_.substr(len, buffer_.size());
}
void Buffer::retrieveAll()
{
	retrieve(readableBytes());
}

std::string Buffer::retrieveAsString(size_t len)
{
	std::string result(peek(), len);
	retrieve(len);
	return result;
}

std::string Buffer::retrieveAllAsString()
{
	return retrieveAsString(readableBytes());
}

