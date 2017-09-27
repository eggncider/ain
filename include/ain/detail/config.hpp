// 
// AIN library detail/config.hpp header file --------------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_DETAIL_CONFIG_HPP
#define AIN_DETAIL_CONFIG_HPP

// Default to a header-only implementation. The user must specifically request
// separate compilation by defining either AIN_SEPARATE_COMPILATION or
// AIN_DYN_LINK (as a DLL/shared library implies separate compilation).
#if !defined(AIN_HEADER_ONLY)
# if !defined(AIN_SEPARATE_COMPILATION)
#  if !defined(AIN_DYN_LINK)
#   define AIN_HEADER_ONLY 1
#  endif // !defined(AIN_DYN_LINK)
# endif // !defined(AIN_SEPARATE_COMPILATION)
#endif // !defined(AIN_HEADER_ONLY)

#if defined(AIN_HEADER_ONLY)
# define AIN_DECL inline
#endif // defined(AIN_HEADER_ONLY)

// If AIN_DECL isn't defined yet define it now.
#if !defined(AIN_DECL)
# define AIN_DECL
#endif // !defined(AIN_DECL)

#endif // AIN_DETAIL_CONFIG_HPP
