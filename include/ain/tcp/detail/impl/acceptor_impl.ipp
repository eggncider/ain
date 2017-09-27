// 
// AIN library tcp/detail/impl/acceptor_impl.ipp header file ----------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_DETAIL_IMPL_ACCEPTOR_IMPL_IPP
#define AIN_TCP_DETAIL_IMPL_ACCEPTOR_IMPL_IPP

//#include <functional>
#include <exception>
#include <boost/bind.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/placeholders.hpp> // for boost::asio::placeholders::error
#include <ain/detail/config.hpp>
#include <ain/tcp/detail/acceptor_impl.hpp>
#include <ain/tcp/service_handler.hpp>

namespace ain {
namespace tcp {
namespace detail {

acceptor_impl::acceptor_impl(boost::asio::io_service& io_service,
	service_handler& service_handler)
	: io_service_(io_service)
	  , acceptor_(io_service)
	  , service_handler_(service_handler)
{
	printf("DEBUG - ain::detail::acceptor_impl constructor\n");
}

bool acceptor_impl::open(const unsigned short port)
{

	try {
		// Set ip address & port
		boost::asio::ip::address address = boost::asio::ip::address_v4::any();
		boost::asio::ip::tcp::endpoint endpoint(address, port);

		// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endpoint);
		acceptor_.listen();

		printf("open(%s:%d) success\n",
			endpoint.address().to_string().c_str(), endpoint.port());
	}
	catch (std::exception& e) {
		printf("open(%d) fail - %s\n", port, e.what());
		return false;
	}

	accept();

	return true;
}

void acceptor_impl::close()
{
	// The server is stopped by cancelling all outstanding asynchronous
	// operations. Once all operations have finished the io_service::run() call
	// will exit.
	acceptor_.close();
	//connection_manager_.stop_all();
}


void acceptor_impl::accept()
{
	connection_.reset(new connection(io_service_, service_handler_));

	/*
	acceptor_.async_accept(connection_->socket()
						, boost::bind(&acceptor_impl::handle_accept
									, this
									, boost::asio::placeholders::error));
									*/
	try
	{
		acceptor_.async_accept(connection_->socket(),
			[this](const boost::system::error_code& ec)
			{
				printf("lambda >>> %s - accept completion. e(%s)\n",
						__FUNCTION__, ec.message().c_str());
				// Check whether the server was stopped by a signal before this
				// completion handler had a chance to run.
				if (!acceptor_.is_open())
				{
					return;
				}

				if (!ec)
				{
					service_handler_.handle_open(connection_);
				}
				accept();
			});
	}
	catch (std::exception &e)
	{
		printf("async_accept exception() - e(%s)\n", e.what());
	}
}

/*
void acceptor_impl::handle_accept(const boost::system::error_code& ec)
{
	printf("%s - accept completion - ec(%s)\n",
			__FUNCTION__, ec.message().c_str());
	// Check whether the server was stopped by a signal before this
	// completion handler had a chance to run.
	if (!acceptor_.is_open())
	{
		return;
	}

	if (!ec)
	{
		connection_->start();
	}

	accept();
}
*/

} // namespace detail
} // namespace tcp 
} // namespace ain

#endif // AIN_TCP_DETAIL_IMPL_ACCEPTOR_IMPL_IPP
