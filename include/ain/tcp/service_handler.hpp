// 
// AIN library tcp/service_handler.hpp header file --------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_SERVICE_HANDLER_HPP
#define AIN_TCP_SERVICE_HANDLER_HPP

#include <string>
#include <ain/detail/config.hpp>
#include <ain/detail/noncopyable.hpp>
#include <ain/tcp/connection.hpp>

namespace ain {
namespace tcp {

class service_handler
{
public: 
	/// Constructor
	explicit service_handler() {}

	/// Destructor
	virtual ~service_handler() {}

	/// Hook methods notified by <acceptor> or <connector>
	/// to handle open.
	virtual void handle_open(connection_ptr c) = 0;

	/// Hook methods notified by <acceptor> or <connector>
	/// to handle close.
	virtual void handle_close(connection_ptr c) = 0;

	/// Handle completion of a read operation.
	virtual void handle_read(connection_ptr c,
			const boost::system::error_code& ec,
			std::size_t bytes_transferred,
			char* buffer) = 0;

	/// Handle completion of a write operation.
	virtual void handle_write(connection_ptr c,
			const boost::system::error_code& ec,
			char* buffer) = 0;
};

} // namespace tcp
} // namespace ain

#endif // AIN_TCP_SERVICE_HANDLER_HPP
