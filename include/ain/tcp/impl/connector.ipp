// 
// AIN library tcp/impl/connector.ipp header file ---------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_IMPL_CONNECTOR_IPP
#define AIN_TCP_IMPL_CONNECTOR_IPP

#include <stdio.h>
#include <ain/detail/config.hpp>
#include <ain/tcp/connector.hpp>
#include <ain/tcp/detail/connector_impl.hpp>

namespace ain {
namespace tcp {

connector::connector(boost::asio::io_service& io_service)
{
	impl_.reset(new ain::tcp::detail::connector_impl(io_service));
}

bool connector::open(const std::string& address, const unsigned short port)
{
	return impl_->open(address, port);
}

void connector::close()
{
	impl_->close();
}

} // namespace tcp
} // namespace ain

#endif // AIN_TCP_IMPL_CONNECTOR_IPP
