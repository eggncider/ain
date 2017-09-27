// 
// AIN library tcp/detail/impl/connector_impl.ipp header file ----------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_DETAIL_IMPL_CONNECTOR_IMPL_IPP
#define AIN_TCP_DETAIL_IMPL_CONNECTOR_IMPL_IPP

#include <boost/asio/ip/address.hpp>
#include <ain/detail/config.hpp>
#include <ain/tcp/detail/connector_impl.hpp>

namespace ain {
namespace tcp {
namespace detail {

connector_impl::connector_impl(boost::asio::io_service& io_service)
	: io_service_(io_service)
//	  , connector_(io_service)
{
	printf("DEBUG - ain::detail::connector_impl constructor\n");
}

bool connector_impl::open(const std::string& address, const unsigned short port)
{

	try {
		// Set ip address & port
		boost::asio::ip::address address = boost::asio::ip::address_v4::any();
		boost::asio::ip::tcp::endpoint endpoint(address, port);

		// Open the connector with the option to reuse the address (i.e. SO_REUSEADDR).
		connector_.open(endpoint.protocol());
		connector_.set_option(boost::asio::ip::tcp::connector::reuse_address(true));
		connector_.bind(endpoint);
		connector_.listen();

		printf("open(%s:%d) success\n"
			, endpoint.address().to_string().c_str(), endpoint.port());
	}
	catch (std::exception& e) {
		printf("open(%d) fail - %s\n", port, e.what());
		return false;
	}

	accept();

	return true;
}

void connector_impl::close()
{
	// The server is stopped by cancelling all outstanding asynchronous
	// operations. Once all operations have finished the io_service::run() call
	// will exit.
	connector_.close();
	//connection_manager_.stop_all();
}


void connector_impl::accept()
{

}

} // namespace detail
} // namespace tcp 
} // namespace ain

#endif // AIN_TCP_DETAIL_IMPL_CONNECTOR_IMPL_IPP
