// Copyright 2017-2018 by Martin Moene
//
// https://github.com/martinmoene/optional-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_OPTIONAL_FUN_LITE_H_INCLUDED
#define TEST_OPTIONAL_FUN_LITE_H_INCLUDED

#include optfun_OPTIONAL_HEADER
#include "nonstd/optional-fun.hpp"

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#include "lest_cpp03.hpp"

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace nonstd { namespace optfun_lite {

inline std::ostream & operator<<( std::ostream & os, monostate const & )
{
    return os << "[monostate]";
}

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

template< typename T >
inline std::ostream & operator<<( std::ostream & os, optional<T> const & v )
{
    using lest::to_string;
    return os << "[optional:" << (v ? to_string(*v) : "[empty]") << "]";
}

}} // namespace nonstd::optfun_lite

namespace lest {

using ::nonstd::optfun_lite::operator<<;

} // namespace lest

#endif // TEST_OPTIONAL_FUN_LITE_H_INCLUDED

// end of file
