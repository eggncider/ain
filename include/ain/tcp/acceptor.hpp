// 
// AIN library tcp/acceptor.hpp header file ---------------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_ACCEPTOR_HPP
#define AIN_TCP_ACCEPTOR_HPP

#include <boost/shared_ptr.hpp>
#include <boost/asio/io_service.hpp>
#include <ain/detail/config.hpp>
#include <ain/detail/noncopyable.hpp>

namespace ain {
namespace tcp {

class service_handler; // forward declaration

namespace detail {
class acceptor_impl; // forward declaration
} // namespace detail

class acceptor 
	: private noncopyable
{
public: 
	/// Constructor
	AIN_DECL explicit acceptor(boost::asio::io_service& io_service,
		service_handler& service_handler);

	/// Open a server socket
	AIN_DECL bool open(const unsigned short port);

	/// Close a server socket (& client sockets)
	AIN_DECL void close();

private:
	boost::shared_ptr<ain::tcp::detail::acceptor_impl> impl_;
};

} // namespace tcp
} // namespace ain

#if defined(AIN_HEADER_ONLY)
# include <ain/tcp/impl/acceptor.ipp>
#endif // defined(AIN_HEADER_ONLY)

#endif // AIN_TCP_ACCEPTOR_HPP
