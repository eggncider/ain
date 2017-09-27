// 
// AIN library tcp/detail/acceptor_impl.hpp header file ---------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_DETAIL_ACCEPTOR_IMPL_HPP
#define AIN_TCP_DETAIL_ACCEPTOR_IMPL_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <ain/detail/config.hpp>
#include <ain/tcp/connection.hpp>

namespace ain {
namespace tcp {
namespace detail {

namespace ain {
namespace tcp {
class service_handler;
} // namespace ain
} // namespace tcp

class acceptor_impl
{
public: 
	/// Constructor
	AIN_DECL explicit acceptor_impl(boost::asio::io_service& io_service,
		service_handler& service_handler);

	/// Open a server socket
	AIN_DECL bool open(const unsigned short port);

	/// Close a server socket (& client sockets) 
	AIN_DECL void close();

private:
	/// Perform an asynchronous accept operation.
	AIN_DECL void accept();

	/// Handle completion of an asynchronous accept operation.
	/// AIN_DECL void handle_accept(const boost::system::error_code& ec);

	/// The io_service used to mperform asynchronous operations.
	boost::asio::io_service& io_service_;

	/// Acceptor used to listen for incomming connections.
	boost::asio::ip::tcp::acceptor acceptor_;

	/// The next connection to be accepted. (client connection)
	connection_ptr connection_;

	///
	service_handler& service_handler_;
};

} // namespace tcp
} // namespace detail 
} // namespace ain

#if defined(AIN_HEADER_ONLY)
# include <ain/tcp/detail/impl/acceptor_impl.ipp>
#endif // defined(AIN_HEADER_ONLY)

#endif // AIN_TCP_DETAIL_ACCEPTOR_IMPL_HPP
