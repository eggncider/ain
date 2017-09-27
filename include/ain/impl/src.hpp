// 
// AIN library impl/src.hpp header file -------------------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_IMPL_SRC_HPP
#define AIN_IMPL_SRC_HPP

#define AIN_SOURCE

#include "ain/detail/config.hpp"

#if defined(AIN_HEADER_ONLY)
# error Do not compile Ain library source with AIN_HEADER_ONLY defined
#endif

#include "ain/impl/tcp_server.ipp"
#include "ain/detail/impl/tcp_server_impl.ipp"

#endif // AIN_IMPL_SRC_HPP
