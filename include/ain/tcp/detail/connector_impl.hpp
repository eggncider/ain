// 
// AIN library tcp/detail/connector_impl.hpp header file ---------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_DETAIL_CONNECTOR_IMPL_HPP
#define AIN_TCP_DETAIL_CONNECTOR_IMPL_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <ain/detail/config.hpp>

namespace ain {
namespace tcp {
namespace detail {

class connector_impl
{
public: 
	/// Constructor
	AIN_DECL explicit connector_impl(boost::asio::io_service& io_service);

	/// Open a client 
	AIN_DECL bool open(const std::string& address, const unsigned short port);

	/// Close a client 
	AIN_DECL void close();

private:
	/// Perform an asynchronous connect operation.
	AIN_DECL void connect();

	boost::asio::io_service& io_service_;
};

} // namespace tcp
} // namespace detail 
} // namespace ain

#if defined(AIN_HEADER_ONLY)
# include <ain/tcp/detail/impl/connector_impl.ipp>
#endif // defined(AIN_HEADER_ONLY)

#endif // AIN_TCP_DETAIL_CONNECTOR_IMPL_HPP
