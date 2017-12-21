//
// Copyright 2014-2017 by Martin Moene
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// optional-fun is inspired by:
// - Simon Brand. Functional exceptionless error-handling with optional and expected. 30 November 2017.
// - Vittorio Romeo. scelta: (experimental) Syntactic sugar for variant and optional types. GitHub

#include "optional-fun-lite.t.h"

namespace {

//
// Functional extension:
//

int  double_int( int arg ) { return 2 * arg; }
void voider_int( int arg ) {}

CASE( "optional map(f): non-void" "[functional]")
{
    const int v = 21;

    EXPECT( 2*v == (optional<int>(v) | map( double_int )).value() );

#if optional_CPP11_OR_GREATER
//    EXPECT( 2*v == optional<int>(v) | map( [](int arg) {return 2*arg; } ).value() );
#endif
}

CASE( "optional map(f): void" "[functional]")
{
    using nonstd::optfun_lite::monostate;
    
    const int v = 21;

    EXPECT( monostate() == (optional<int>(v) | map( voider_int )).value() );

#if optional_CPP11_OR_GREATER
//    EXPECT( monostate() == optional<int>(v) | map( [](int arg) -> void {} ).value() );
#endif
}

CASE( "optional map_or(f): " "[functional]")
{
    EXPECT( 14 == (optional<int>( 7 ) | map_or( double_int, 42 )) );
    EXPECT( 42 == (optional<int>(   ) | map_or( double_int, 42 )) );
}

int seven() { return 7; }

CASE( "optional map_or_else(f): " "[functional]")
{
    EXPECT( 14 == (optional<int>( 7 ) | map_or_else( double_int, seven )) );
    EXPECT(  7 == (optional<int>(   ) | map_or_else( double_int, seven )) );
}

optional<int> double_opt( int arg ) { return 2 * arg; }
optional<int> fail_opt  ( int arg ) { return nullopt; }

CASE( "optional and_then(f): success" "[functional]")
{
    const int  v = 21;

    EXPECT( 2*v == (optional<int>(v) | then(     double_opt )).value() );
    EXPECT( 2*v == (optional<int>(v) | and_then( double_opt )).value() );
}

CASE( "optional and_then(f): fail" "[functional]")
{
    EXPECT_NOT( (optional<int>(7)
        | and_then( double_opt )
        | and_then( fail_opt   )
        | and_then( double_opt )).has_value() );
}

int  fun_or_else_nonvoid() { return 7; }
void fun_or_else_void()    {}

CASE( "optional or_else(f): non-void" "[functional]")
{
    EXPECT(                    -1 == (optional<int>(-1) | or_else( fun_or_else_nonvoid )).value() );
    EXPECT( fun_or_else_nonvoid() == (optional<int>(  ) | or_else( fun_or_else_nonvoid )).value() );
}

CASE( "optional or_else(f): void" "[functional]")
{
    EXPECT(  -1 == (optional<int>(-1) | or_else( fun_or_else_void )).value() );
    EXPECT_NOT(    (optional<int>(  ) | or_else( fun_or_else_void )).has_value() );
}

CASE( "optional and_(u): " "[functional]")
{
    EXPECT(  42 == (optional<int>(7) | and_( 42 )).value() );
    EXPECT_NOT(    (optional<int>( ) | and_( 42 )).has_value() );
}

CASE( "optional or_(rhs): " "[functional]")
{
    EXPECT(  7 == (optional<int>(7) | or_( 42 )) );
    EXPECT( 42 == (optional<int>( ) | or_( 42 )) );
}

//CASE( "optional take(): " "[functional]")
//{
//}

//
// Negative tests:
//

//
// Tests that print information:
//

//
// Issues:
//

} // anonymous namespace

// end of file
