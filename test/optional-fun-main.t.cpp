// Copyright 2017-2018 by Martin Moene
//
// https://github.com/martinmoene/optional-fun-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "optional-fun-main.t.hpp"

#define optfun_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define optfun_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "optional-fun-lite version" "[.version]" )
{
    optfun_PRESENT( optional_fun_lite_MAJOR );
    optfun_PRESENT( optional_fun_lite_MINOR );
    optfun_PRESENT( optional_fun_lite_PATCH );
    optfun_PRESENT( optional_fun_lite_VERSION );
}

CASE( "optional-fun-lite configuration" "[.config]" )
{
    optfun_PRESENT( optfun_USES_BOOST_OPTIONAL );
    optfun_PRESENT( optfun_USES_OPTIONAL_LITE );
    optfun_PRESENT( optfun_USES_STD_OPTIONAL );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    optfun_PRESENT( __cplusplus );

#if _MSVC_LANG
    optfun_PRESENT( _MSVC_LANG );
#else
    optfun_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "compiler version" "[.compiler]" )
{
#if optfun_CPP17_OR_GREATER
    std::cout << "(Compiler version not available: C++17 or higher)\n";
#else
    optfun_PRESENT( optfun_COMPILER_CLANG_VERSION );
    optfun_PRESENT( optfun_COMPILER_GNUC_VERSION );
    optfun_PRESENT( optfun_COMPILER_MSVC_VERSION );
#endif
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
#if optfun_CPP17_OR_GREATER
    std::cout << "(Presence of C++ language features not available: C++17 or higher)\n";
#else
    optfun_PRESENT( optfun_HAVE_CONSTEXPR_11 );
    optfun_PRESENT( optfun_HAVE_CONSTEXPR_14 );
    optfun_PRESENT( optfun_HAVE_NOEXCEPT );
    optfun_PRESENT( optfun_HAVE_REF_QUALIFIER );
#endif
}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#ifdef _HAS_CPP0X
    optfun_PRESENT( _HAS_CPP0X );
#else
    optfun_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++98 -I../include -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++03 -I../include -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++0x -I../include -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++11 -I../include -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++14 -I../include -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++17 -I../include -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass

cl -EHsc -I../include optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
#endif

// end of file
