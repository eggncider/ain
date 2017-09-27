// 
// AIN library tcp/impl/connection.ipp header file --------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_IMPL_CONNECTION_IPP
#define AIN_TCP_IMPL_CONNECTION_IPP

#include <stdio.h>
#include <exception>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/read_at.hpp>
#include <ain/detail/config.hpp>
#include <ain/tcp/connection.hpp>
#include <ain/tcp/service_handler.hpp>

namespace ain {
namespace tcp {

connection::connection(boost::asio::io_service& io_service,
	service_handler& service_handler)
	: socket_(io_service),
		service_handler_(service_handler)
{
	printf("%s constructor...\n", __FUNCTION__);
}

connection::~connection()
{
	printf("%s destructor...)\n", __FUNCTION__);
}

boost::asio::ip::tcp::socket& connection::socket()
{
	return socket_;
}

void connection::read(char* buffer, unsigned int buffer_size)
{
	printf("%s....\n", __FUNCTION__);

	auto self(shared_from_this());
	// NOTE:
	// - If you do not capture self, you meet error (Operation canceled).
	socket_.async_read_some(boost::asio::buffer(buffer, buffer_size),
		[this, self, buffer](boost::system::error_code ec,
								std::size_t bytes_transferred)
		{
			printf("DEBUG::%s - ec(%s) bytes_transferred(%ld)\n",
					__FUNCTION__,
					ec.message().c_str(), bytes_transferred);
			if (!ec)
			{
				service_handler_.handle_read(shared_from_this(),
					ec,
					bytes_transferred,
					buffer);
			}
			else if (ec != boost::asio::error::operation_aborted)
			{	
				service_handler_.handle_close(shared_from_this());
				close();
			}
		});
}

/*
void connection::read_at(unsigned int offset, char* buffer, unsigned int buffer_size)
{
	printf("%s....\n", __FUNCTION__);

	try
	{
		boost::asio::async_read_at(socket_, offset,
			boost::asio::buffer(buffer, buffer_size),
				boost::bind(&connection::handle_read, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred,
					buffer));
	}
	catch (std::exception &e)
	{
		printf("async_read_some error() - e(%s)\n", e.what());
	}
}
*/

void connection::write(char* buffer, unsigned int buffer_size)
{
	printf("%s....\n", __FUNCTION__);

	auto self(shared_from_this());
	// NOTE:
	// - If you do not capture self, you meet error (Operation canceled).
	socket_.async_write_some(boost::asio::buffer(buffer, buffer_size),
		[this, self, buffer](boost::system::error_code ec, std::size_t)
		{
			printf("DEBUG::%s - ec(%s) TEST<buffer(%p)>\n",
					__FUNCTION__,
					ec.message().c_str(), buffer);

			// NOTE: user callback... ^^;
			service_handler_.handle_write(shared_from_this(), ec, buffer);
		});
}

void connection::close()
{
	printf("%s - %s:%d\n",
			__FUNCTION__,
			socket_.remote_endpoint().address().to_string().c_str(),
			socket_.remote_endpoint().port());

	socket_.close();
}

/*
void connection::handle_read(const boost::system::error_code& ec,
								std::size_t bytes_transferred,
								char* buffer)
{
	printf("DEBUG::%s - ec(%s) bytes_transferred(%ld)\n",
			__FUNCTION__,
			ec.message().c_str(), bytes_transferred);
	if (!ec)
	{
		// NOTE: user callback... ^^;
		service_handler_.handle_read(shared_from_this(),
					ec,
					bytes_transferred,
					buffer);
	}
	else if (ec != boost::asio::error::operation_aborted)
	{
		// NOTE: ec(2:End of file) - client close socket.
		service_handler_.handle_close(shared_from_this());
		close();
	}
}
*/

} // namespace tcp 
} // namespace ain

#endif // AIN_TCP_IMPL_ACCEPTOR_IMPL_IPP
