#pragma once

#include<functional>
namespace Ptole
{
	namespace  net
	{
		class Connection;
		class Buffer;
		using Callback = std::function<void()>;
		using MessageCallback = std::function<void(Connection* connPtr, Buffer* buffer)>;;
	}
}