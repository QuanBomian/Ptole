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
			void retrieve(size_t len);
			void retrieveAll();
			std::string retrieveAsString(size_t len);
			std::string retrieveAllAsString();

		private:
			std::string buffer_;



		};
		
	}
}
