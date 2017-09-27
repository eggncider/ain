// 
// AIN library tcp/connector.hpp header file --------------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_CONNECTOR_HPP
#define AIN_TCP_CONNECTOR_HPP

#include <memory>
#include <string>
#include <boost/asio/io_service.hpp>
#include <ain/detail/config.hpp>
#include <ain/detail/noncopyable.hpp>

namespace ain {
namespace tcp {

namespace detail {
class connector_impl;
} // namespace detail

class connector 
	: private noncopyable
{
public: 
	/// Constructor
	AIN_DECL explicit connector(boost::asio::io_service& io_service);

	/// Open a client 
	AIN_DECL bool open(const std::string& address, const unsigned short port);

	/// Close a client 
	AIN_DECL void close();

private:
	std::shared_ptr<ain::tcp::detail::connector_impl> impl_;
};

} // namespace tcp
} // namespace ain

#if defined(AIN_HEADER_ONLY)
# include <ain/tcp/impl/connector.ipp>
#endif // defined(AIN_HEADER_ONLY)

#endif // AIN_TCP_CONNECTOR_HPP
