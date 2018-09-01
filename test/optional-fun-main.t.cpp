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

CASE( "__cplusplus" "[.stdc++]" )
{
    optfun_PRESENT( __cplusplus );

#if _MSVC_LANG
    optfun_PRESENT( _MSVC_LANG );
#else
    optfun_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "optional-fun-lite configuration" "[.config]" )
{
#if optfun_HAVE_STD_OPTIONAL
    std::cout << "Have std::optional\n";
#else
    std::cout << "No std::optional\n";
#endif

#if optfun_USES_STD_OPTIONAL
    std::cout << "Using std::optional\n";
#else
    std::cout << "Using nonstd::optional\n";
#endif
}

#if !optfun_HAVE_STD_OPTIONAL

CASE( "compiler version" "[.compiler]" )
{
#if optfun_COMPILER_GNUC_VERSION
    optfun_PRESENT( optfun_COMPILER_GNUC_VERSION );
#else
    optfun_ABSENT(  optfun_COMPILER_GNUC_VERSION );
#endif

#if optfun_COMPILER_MSVC_VERSION
    optfun_PRESENT( optfun_COMPILER_MSVC_VERSION );
#else
    optfun_ABSENT(  optfun_COMPILER_MSVC_VERSION );
#endif
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
#if optfun_HAVE_AUTO
    optfun_PRESENT( optfun_HAVE_AUTO );
#else
    optfun_ABSENT(  optfun_HAVE_AUTO );
#endif

#if optfun_HAVE_NULLPTR
    optfun_PRESENT( optfun_HAVE_NULLPTR );
#else
    optfun_ABSENT(  optfun_HAVE_NULLPTR );
#endif

#if optfun_HAVE_STATIC_ASSERT
    optfun_PRESENT( optfun_HAVE_STATIC_ASSERT );
#else
    optfun_ABSENT(  optfun_HAVE_STATIC_ASSERT );
#endif

#if optfun_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
    optfun_PRESENT( optfun_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#else
    optfun_ABSENT(  optfun_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#endif

#if optfun_HAVE_ALIAS_TEMPLATE
    optfun_PRESENT( optfun_HAVE_ALIAS_TEMPLATE );
#else
    optfun_ABSENT(  optfun_HAVE_ALIAS_TEMPLATE );
#endif

#if optfun_HAVE_CONSTEXPR_11
    optfun_PRESENT( optfun_HAVE_CONSTEXPR_11 );
#else
    optfun_ABSENT(  optfun_HAVE_CONSTEXPR_11 );
#endif

#if optfun_HAVE_CONSTEXPR_14
    optfun_PRESENT( optfun_HAVE_CONSTEXPR_14 );
#else
    optfun_ABSENT(  optfun_HAVE_CONSTEXPR_14 );
#endif

#if optfun_HAVE_ENUM_CLASS
    optfun_PRESENT( optfun_HAVE_ENUM_CLASS );
#else
    optfun_ABSENT(  optfun_HAVE_ENUM_CLASS );
#endif

#if optfun_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE
    optfun_PRESENT( optfun_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#else
    optfun_ABSENT(  optfun_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#endif

#if optfun_HAVE_EXPLICIT_CONVERSION
    optfun_PRESENT( optfun_HAVE_EXPLICIT_CONVERSION );
#else
    optfun_ABSENT(  optfun_HAVE_EXPLICIT_CONVERSION );
#endif

#if optfun_HAVE_INITIALIZER_LIST
    optfun_PRESENT( optfun_HAVE_INITIALIZER_LIST );
#else
    optfun_ABSENT(  optfun_HAVE_INITIALIZER_LIST );
#endif

#if optfun_HAVE_IS_DEFAULT
    optfun_PRESENT( optfun_HAVE_IS_DEFAULT );
#else
    optfun_ABSENT(  optfun_HAVE_IS_DEFAULT );
#endif

#if optfun_HAVE_IS_DELETE
    optfun_PRESENT( optfun_HAVE_IS_DELETE );
#else
    optfun_ABSENT(  optfun_HAVE_IS_DELETE );
#endif

#if optfun_HAVE_NOEXCEPT
    optfun_PRESENT( optfun_HAVE_NOEXCEPT );
#else
    optfun_ABSENT(  optfun_HAVE_NOEXCEPT );
#endif

#if optfun_HAVE_REF_QUALIFIER
    optfun_PRESENT( optfun_HAVE_REF_QUALIFIER );
#else
    optfun_ABSENT(  optfun_HAVE_REF_QUALIFIER );
#endif
}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#if optfun_HAVE_ARRAY
    optfun_PRESENT( optfun_HAVE_ARRAY );
#else
    optfun_ABSENT(  optfun_HAVE_ARRAY );
#endif

#if optfun_HAVE_CONDITIONAL
    optfun_PRESENT( optfun_HAVE_CONDITIONAL );
#else
    optfun_ABSENT(  optfun_HAVE_CONDITIONAL );
#endif

#if optfun_HAVE_CONTAINER_DATA_METHOD
    optfun_PRESENT( optfun_HAVE_CONTAINER_DATA_METHOD );
#else
    optfun_ABSENT(  optfun_HAVE_CONTAINER_DATA_METHOD );
#endif

#if optfun_HAVE_REMOVE_CV
    optfun_PRESENT( optfun_HAVE_REMOVE_CV );
#else
    optfun_ABSENT(  optfun_HAVE_REMOVE_CV );
#endif

#if optfun_HAVE_SIZED_TYPES
    optfun_PRESENT( optfun_HAVE_SIZED_TYPES );
#else
    optfun_ABSENT(  optfun_HAVE_SIZED_TYPES );
#endif

#if optfun_HAVE_TYPE_TRAITS
    optfun_PRESENT( optfun_HAVE_TYPE_TRAITS );
#else
    optfun_ABSENT(  optfun_HAVE_TYPE_TRAITS );
#endif

#if _HAS_CPP0X
    optfun_PRESENT( _HAS_CPP0X );
#else
    optfun_ABSENT(  _HAS_CPP0X );
#endif
}

#endif // optfun_HAVE_STD_OPTIONAL

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o optional-fun-lite.t.exe optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass

cl -EHsc -I../include/nonstd optional-fun-lite.t.cpp && optional-fun-lite.t.exe --pass
#endif

// end of file
