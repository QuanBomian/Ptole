#pragma once
#include<string>
namespace Ptole
{
	namespace net
	{
		class Buffer
		{
		public:

			const char * peek() const;
			int readableBytes() const;
			void append(const std::string& data);
			void retrive(size_t len);
			void retriveAll();
			std::string retriveAsString(size_t len);
			std::string retriveAllAsString();

		private:
			std::string buffer_;



		};
		
	}
}
