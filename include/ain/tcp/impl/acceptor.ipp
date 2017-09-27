// 
// AIN library tcp/impl/acceptor.ipp header file ----------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_IMPL_ACCEPTOR_IPP
#define AIN_TCP_IMPL_ACCEPTOR_IPP

#include <ain/detail/config.hpp>
#include <ain/tcp/acceptor.hpp>
#include <ain/tcp/detail/acceptor_impl.hpp>

namespace ain {
namespace tcp {

acceptor::acceptor(boost::asio::io_service& io_service,
	service_handler& service_handler)
{
	impl_.reset(new ain::tcp::detail::acceptor_impl(io_service,
		service_handler));
}

bool acceptor::open(const unsigned short port)
{
	return impl_->open(port);
}

void acceptor::close()
{
	impl_->close();
}

} // namespace tcp
} // namespace ain

#endif // AIN_TCP_IMPL_ACCEPTOR_IPP
