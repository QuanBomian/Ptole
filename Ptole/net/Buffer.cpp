
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

void Buffer::retrive(size_t len)
{
	buffer_ = buffer_.substr(len, buffer_.size());
}
void Buffer::retriveAll()
{
	retrive(readableBytes());
}

std::string Buffer::retriveAsString(size_t len)
{
	std::string result(peek(), len);
	retrive(len);
	return result;
}

std::string Buffer::retriveAllAsString()
{
	return retriveAsString(readableBytes());
}

