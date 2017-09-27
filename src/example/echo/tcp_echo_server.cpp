#include <stdio.h>
#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <ain/tcp/acceptor.hpp>
#include <ain/tcp/service_handler.hpp>

using ain::tcp::service_handler;
using ain::tcp::connection_ptr;

class echo_handler
	: public service_handler
{
public:
	void handle_open(connection_ptr c)
	{
		printf("%s - remote_endpoint(%s:%d)\n",
			__FUNCTION__,
			c->socket().remote_endpoint().address().to_string().c_str(),
			c->socket().remote_endpoint().port());

		char* buffer = (char*)malloc(8192);
		c->read(buffer, 8192);
	}

	void handle_close(connection_ptr c)
	{
		printf("%s - ... ^^\n", __FUNCTION__);
	}

	void handle_read(connection_ptr c,
		const boost::system::error_code& ec,
		std::size_t bytes_transferred,
		char* buffer)
	{
		printf("%s - remote_endpoint(%s:%d) ec(%s) bytes_transferred(%ld)\n",
			__FUNCTION__,
			c->socket().remote_endpoint().address().to_string().c_str(),
			c->socket().remote_endpoint().port(),
			ec.message().c_str(), bytes_transferred
			);

		buffer[bytes_transferred] = '\0';
		printf("%s - read data(%s)\n", __FUNCTION__, buffer);

		c->write(buffer, bytes_transferred);
		c->read(buffer, 8192);
	}

	void handle_write(connection_ptr c,
		const boost::system::error_code& ec,
		char* buffer)
	{
		printf("%s - remote_endpoint(%s:%d) ec(%s)\n",
			__FUNCTION__,
			c->socket().remote_endpoint().address().to_string().c_str(),
			c->socket().remote_endpoint().port(),
			ec.message().c_str()
			);
	}
};

int main(int argc, char** argv)
{
	printf("AIN START... :)\n");

	boost::asio::io_service io_service;
	echo_handler eh;

	ain::tcp::acceptor dark(io_service, eh);
	dark.open(7905);

	boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(1));
	timer.wait();

	printf("AIN RUN...\n");
	io_service.run();

	printf("AIN END...\n");

	return 0;
}
