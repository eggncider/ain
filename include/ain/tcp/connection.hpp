// 
// AIN library tcp/connection.hpp header file -------------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_TCP_CONNECTION_HPP
#define AIN_TCP_CONNECTION_HPP

#include <boost/array.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <ain/detail/config.hpp>
#include <ain/detail/noncopyable.hpp>

namespace ain {
namespace tcp {

class service_handler;

class connection 
	: public boost::enable_shared_from_this<connection>
	  , private noncopyable
{
public: 
	/// Constructor
	AIN_DECL explicit connection(boost::asio::io_service& io_service,
			service_handler& service_handler);

	/// Destructor
	AIN_DECL ~connection();

	/// Get the socket associated with the connection.
	boost::asio::ip::tcp::socket& socket();

	/// Perform an asynchronous read operation.
	AIN_DECL void read(char* buffer, unsigned int buffer_size);

	/// Perform an asynchronous write operation.
	AIN_DECL void write(char* buffer, unsigned int buffer_size);

	/// 
	AIN_DECL void close();

private:

	/// Socket for the connection.
	boost::asio::ip::tcp::socket socket_;

	/// Service handler
	service_handler& service_handler_;

	/*/ Handle completion of a read operation
	AIN_DECL void handle_read(const boost::system::error_code& ec,
			std::size_t bytes_transferred,
			char* buffer);
	*/
};

typedef boost::shared_ptr<connection> connection_ptr;

} // namespace tcp
} // namespace ain

#if defined(AIN_HEADER_ONLY)
# include <ain/tcp/impl/connection.ipp>
#endif // defined(AIN_HEADER_ONLY)

#endif // AIN_TCP_CONNECTION_HPP
