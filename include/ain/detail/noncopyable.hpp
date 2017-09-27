// 
// AIN library detail/noncopyable.hpp header file ---------------------------//
//
// Copyright (c) 2017 Dark (dark at eggncider dot com)
//
// Distributed under Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AIN_DETAIL_NONCOPYABLE_HPP
#define AIN_DETAIL_NONCOPYABLE_HPP

namespace ain {
namespace detail {

class noncopyable
{
protected:
	noncopyable() {}
	~noncopyable() {}
private:
	noncopyable(const noncopyable&);
	const noncopyable& operator=(const noncopyable&);
};

} // namespace detail

using ain::detail::noncopyable;

} // namespace ain 

#endif // AIN_DETAIL_NONCOPYABLE_HPP
