//
// Copyright (c) 2017 Martin Moene
//
// https://github.com/martinmoene/optional-fun-lite
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// optional-fun is inspired by:
// - Simon Brand. Functional exceptionless error-handling with optional and expected. 30 November 2017.
// - Vittorio Romeo. scelta: (experimental) Syntactic sugar for variant and optional types. GitHub

#pragma once

#ifndef NONSTD_OPTIONAL_FUN_LITE_HPP
#define NONSTD_OPTIONAL_FUN_LITE_HPP

#define  optional_fun_lite_VERSION "0.1.0"

// Configuration:

#ifndef  gsl_FEATURE_HAVE_IMPLICIT_MACRO
# define gsl_FEATURE_HAVE_IMPLICIT_MACRO  1
#endif

#ifndef optfun_CONFIG_USE_OWN_OPTIONAL
#endif

#ifndef optfun_CONFIG_USE_BOOST_OPTIONAL
#endif

#ifndef optfun_CONFIG_USE_STD_OPTIONAL
#endif

// Detect kind of optional used, unless specified via configuration:

#if ! (defined( optfun_CONFIG_USE_OWN_OPTIONAL   ) || \
       defined( optfun_CONFIG_USE_BOOST_OPTIONAL ) || \
       defined( optfun_CONFIG_USE_STD_OPTIONAL   ) )

#if defined( optional_lite_VERSION )
# define optfun_USES_OPTIONAL_LITE  1
#elif defined( BOOST_OPTIONAL_OPTIONAL_FLC_19NOV2002_HPP )
# define optfun_USES_BOOST_OPTIONAL  1
# include <boost/none.hpp>
# include <boost/optional/bad_optional_access.hpp>
#else
# define optfun_USES_STD_OPTIONAL  1
#endif
#endif

// Compiler detection:

#define optfun_CPP11_OR_GREATER  ( __cplusplus >= 201103L )
#define optfun_CPP14_OR_GREATER  ( __cplusplus >= 201402L /* || _MSVC_LANG >= 201402L */ )
#define optfun_CPP17_OR_GREATER  ( __cplusplus >= 201703L    || _MSVC_LANG >= 201703L    )

// optonal functional extensions in three parts:
// 1. nudge optional, common to all language versions
// 2. C++17 and later
// 3. before C++17

//
// 1. nudge optional:
// - provide optional used in namespace nonstd:
// - provide has_value() free function to accomodate differences between optional-s
//

namespace nonstd {

#if optfun_USES_OPTIONAL_LITE

// optional-lite already is in namespace nonstd

namespace optfun_lite {

template< typename T >
inline bool has_value( nonstd::optional<T> const & o ) { return o.has_value(); }

template< typename T >
inline bool value( nonstd::optional<T> const & o ) { return o.has_value(); }

}

#elif optfun_USES_STD_OPTIONAL

using std::optional;
using std::nullopt;
using std::bad_optional_access;
using std::make_optional;

namespace optfun_lite {

template< typename T >
inline bool has_value( std::optional<T> const & o ) { return o.has_value(); }

template< typename T >
inline bool value( nonstd::optional<T> const & o ) { return o.has_value(); }

}

#elif optfun_USES_BOOST_OPTIONAL

using boost::optional;
using boost::bad_optional_access;
using boost::make_optional;

namespace { boost::none_t const & nullopt = boost::none; }

namespace optfun_lite {

template< typename T >
inline bool has_value( boost::optional<T> const & o ) { return !!o; }

}

#endif // optfun_USING_STD_OPTIONAL

} // namespace nonstd

//
// 2. C++7 and later:
//

#if optfun_CPP17_OR_GREATER

#include <functional>
#include <type_traits>

//
// class monostate:
//

namespace nonstd::optfun_lite {

class monostate {};

constexpr inline bool operator< ( monostate, monostate ) noexcept { return false; }
constexpr inline bool operator> ( monostate, monostate ) noexcept { return false; }
constexpr inline bool operator<=( monostate, monostate ) noexcept { return true;  }
constexpr inline bool operator>=( monostate, monostate ) noexcept { return true;  }
constexpr inline bool operator==( monostate, monostate ) noexcept { return true;  }
constexpr inline bool operator!=( monostate, monostate ) noexcept { return false; }

} // namespace nonstd::optfun_lite

// specialize the std::hash algorithm:

namespace std {

template<>
struct hash< ::nonstd::optfun_lite::monostate >
{
public:
    std::size_t operator()( ::nonstd::optfun_lite::monostate const & /*v*/ ) const noexcept
    {
        return 0;
    }
};

} //namespace std

//
// functional algorithms:
//

namespace nonstd { namespace optfun_lite {

// map(f):
// - perform operation `U f(T)` on optional's content if present and return an optional<U>.
// - perform operation `void f(T)` on optional's content if present and return an optional<monostate>..

template< typename F >
struct map
{
    F f;

    map( F f_ )
    : f( f_ ) {}

    // map(f): perform operation `U f(T)` on optional's
    // content if present and return an optional<U>.

    template< typename T >
    std::enable_if_t<
        !std::is_void_v< std::invoke_result_t<F,T> >
        , optional< std::invoke_result_t<F,T> >
    >
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return std::invoke( f, o.value() );
        }
        return nullopt;
    }

    // map(f): perform operation `void f(T)` on optional's
    // content if present and return an optional<monostate>.

    template< typename T >
    std::enable_if_t<
        std::is_void_v< std::invoke_result_t<F,T> >
        , optional< monostate >
    >
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            std::invoke( f, o.value() );
            return monostate{};
        }
        return nullopt;
    }
};

// map_or(f, u): perform operation `U f(T)` on optional's
// content if present and return it, otherwise return u.

template< typename F, typename U >
struct map_or
{
    F f;
    U const & u;

    map_or( F f_, U const & u_ )
    : f( f_ ), u( u_) {}

    template< typename T >
    U
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return std::invoke( f, o.value() );
        }
        return u;
    }
};

// map_or_else(f, u): perform operation `U f(T)` on optional's
// content if present and return it, otherwise return operation u().

template< typename F, typename U >
struct map_or_else
{
    F f;
    U u;

    map_or_else( F f_, U u_ )
    : f( f_ ), u( u_) {}

    template< typename T >
    std::invoke_result_t<U>
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return std::invoke( f, o.value() );
        }
        return u();
    }
};

// and_then(f): return operation `optional<U> f(T)` on optional's
// content if present and return an optional<U>.

template< typename F >
struct and_then
{
    F f;

    and_then( F f_ )
    : f( f_ ) {}

    template< typename T >
    std::invoke_result_t<F,T>
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return std::invoke( f, o.value() );
        }
        return nullopt;
    }
};

// alias then to and_then:

template< typename F >
struct then : and_then<F>
{
    then( F f )
    : and_then<F>( f ) {}
};

// or_else(f):
// - return the call `R f()` if optional is empty, otherwise return optional.
// - call `void f()` and return nullopt if optional is empty, otherwise return optional.

template< typename F >
struct or_else
{
    F f;

    or_else( F f_ )
    : f( f_ ) {}

    // or_else(f): return the call `R f()` if optional is empty, otherwise return optional.

    template< typename T >
    typename std::enable_if_t<
        ! std::is_void_v< std::invoke_result_t<F> >
        , optional<T>
    >
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return o;
        }
        return f();
    }

    // or_else(f): call `void f()` and return nullopt if optional is empty, otherwise return optional.

    template< typename T >
    typename std::enable_if_t<
        std::is_void_v< std::invoke_result_t<F> >
        , optional<T>
    >
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return o;
        }

        f();
        return nullopt;
    }
};

// and_(): return `u` if optional has content, otherwise return an empty optional.

template< typename U >
struct and_
{
    U const & u;

    and_( U u_ )
    : u( u_ ) {}

    template< typename T >
    optional< typename std::decay<U>::type >
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return u;
        }

        return nullopt;
    }
};

// or_(): return the current value if non-empty, otherwise return `rhs`.

template< typename U >
struct or_
{
    U const & u;

    or_( U u_ )
    : u( u_ ) {}

    template< typename T >
    auto operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return o.value();
        }
        return u;
    }
};

//// take(): Take the value out of the optional, leaving it empty and return it:
//
//optional_f take()
//{
//    optional_f result; result.swap( *this );
//    return result;
//}

// operator|(optional, algorithm): connect operation to optional:

template< typename T, typename F >
auto operator|( optional<T> o, F f )
{
    return std::invoke( f, o );
}

} // namespace optfun_lite

// keep monostate local to optfun_lite:
// using optfun_lite::monostate;

using optfun_lite::map;
using optfun_lite::map_or;
using optfun_lite::map_or_else;
using optfun_lite::then;
using optfun_lite::and_then;
using optfun_lite::or_else;
using optfun_lite::and_;
using optfun_lite::or_;
//using optfun_lite::take;

using optfun_lite::operator|;

} // namespace nonstd

#else // optfun_CPP17_OR_GREATER

//
// 3. Before C++17
//

// half-open range [lo..hi):
#define optfun_BETWEEN( v, lo, hi ) ( lo <= v && v < hi )

#if defined(_MSC_VER) && !defined(__clang__)
# define optfun_COMPILER_MSVC_VERSION   (_MSC_VER / 100 - 5 - (_MSC_VER < 1900))
#else
# define optfun_COMPILER_MSVC_VERSION   0
#endif

#if defined __GNUC__
# define optfun_COMPILER_GNUC_VERSION  __GNUC__
#else
# define optfun_COMPILER_GNUC_VERSION    0
#endif

#if optfun_BETWEEN(optfun_COMPILER_MSVC_VERSION, 7, 14 )
# pragma warning( push )
# pragma warning( disable: 4345 )   // initialization behavior changed
#endif

#if optfun_BETWEEN(optfun_COMPILER_MSVC_VERSION, 7, 15 )
# pragma warning( push )
# pragma warning( disable: 4814 )   // in C++14 'constexpr' will not imply 'const'
#endif

// Presence of C++11 language features:

#if optfun_CPP11_OR_GREATER || optfun_COMPILER_MSVC_VERSION >= 10
# define optfun_HAVE_AUTO  1
# define optfun_HAVE_NULLPTR  1
# define optfun_HAVE_STATIC_ASSERT  1
#endif

#if optfun_CPP11_OR_GREATER || optfun_COMPILER_MSVC_VERSION >= 12
# define optfun_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  1
# define optfun_HAVE_INITIALIZER_LIST  1
#endif

#if optfun_CPP11_OR_GREATER || optfun_COMPILER_MSVC_VERSION >= 14
# define optfun_HAVE_ALIAS_TEMPLATE  1
# define optfun_HAVE_CONSTEXPR_11  1
# define optfun_HAVE_ENUM_CLASS  1
# define optfun_HAVE_EXPLICIT_CONVERSION  1
# define optfun_HAVE_IS_DEFAULT  1
# define optfun_HAVE_IS_DELETE  1
# define optfun_HAVE_NOEXCEPT  1
# define optfun_HAVE_REF_QUALIFIER  1
#endif

// Presence of C++14 language features:

#if optfun_CPP14_OR_GREATER
# define optfun_HAVE_CONSTEXPR_14  1
#endif

// Presence of C++17 language features:

// ...

// For the rest, consider VC14 as C++11 for optional-lite:

//#if      optfun_COMPILER_MSVC_VERSION >= 14
//# undef  optfun_CPP11_OR_GREATER
//# define optfun_CPP11_OR_GREATER  1
//#endif

// C++ feature usage:

#if      optfun_HAVE_CONSTEXPR_11
# define optfun_constexpr  constexpr
#else
# define optfun_constexpr  /*constexpr*/
#endif

#if      optfun_HAVE_CONSTEXPR_14
# define optfun_constexpr14  constexpr
#else
# define optfun_constexpr14  /*constexpr*/
#endif

#if      optfun_HAVE_NOEXCEPT
# define optfun_noexcept  noexcept
#else
# define optfun_noexcept  /*noexcept*/
#endif

#if      optfun_HAVE_REF_QUALIFIER
# define optfun_ref_qual  &
# define optfun_refref_qual  &&
#else
# define optfun_ref_qual  /*&*/
# define optfun_refref_qual  /*&&*/
#endif

// additional includes:

#if optfun_CPP11_OR_GREATER
# include <functional>
#endif

//
// type traits:
//

#define  optfun_INVOKE(f,t)           f(t)

# define optfun_INVOKE_RESULT_T(F,T)  typename ::nonstd::optfun_lite::detail::result_of<F>::type
# define optfun_RESULT_OF_T(F)        typename ::nonstd::optfun_lite::detail::result_of<F>::type

#if      optfun_CPP11_OR_GREATER
# define optfun_FORWARD(T, arg)  std::forward<T>(arg)
# define optfun_MOVE(      arg)  std::move(arg)
#else
# define optfun_FORWARD(T, arg)  arg
# define optfun_MOVE(      arg)  arg
#endif // optfun_CPP11_OR_GREATER

//#if optfun_CPP11_OR_GREATER
//
//namespace nonstd { namespace optfun_lite { namespace detail {
//
//    using std::decay;
//    using std::enable_if;
//    using std::is_void;
//
//}}}
//
//#else // optfun_CPP11_OR_GREATER

namespace nonstd { namespace optfun_lite { namespace detail {

template< typename T, T v >
struct integral_constant
{
    typedef integral_constant< T, v > type;
    typedef T value_type;
    static const T value = v;
};

typedef integral_constant< bool, true  > true_type;
typedef integral_constant< bool, false > false_type;

template< bool B, typename T, typename F > struct conditional              { typedef T type; };
template<         typename T, typename F > struct conditional<false, T, F> { typedef F type; };

template< bool B, typename T = void > struct enable_if {};
template< typename T >                struct enable_if<true, T> { typedef T type; };

template< typename T, typename U >    struct is_same       : false_type{};
template< typename T>                 struct is_same<T, T> : true_type {};

template< typename T>                 struct is_array : false_type {};
template< typename T>                 struct is_array<T[]> : true_type {};
template< typename T, std::size_t N > struct is_array<T[N]> : true_type {};

template< typename T>                 struct is_function        : false_type{};
template< typename R, typename T1 >   struct is_function<R(T1)> : true_type {};

template< typename T > struct remove_reference      {typedef T type;};
template< typename T > struct remove_reference<T&>  {typedef T type;};
//template< typename T > struct remove_reference<T&&> {typedef T type;};

template< typename T > struct remove_const          { typedef T type; };
template< typename T > struct remove_const<const T> { typedef T type; };

template< typename T > struct remove_volatile             { typedef T type; };
template< typename T > struct remove_volatile<volatile T> { typedef T type; };

template< typename T > struct remove_cv { typedef typename remove_volatile<typename remove_const<T>::type>::type type; };

template< typename T >                struct remove_extent       { typedef T type; };
template< typename T >                struct remove_extent<T[]>  { typedef T type; };
template< typename T, std::size_t N > struct remove_extent<T[N]> { typedef T type; };

namespace detail_ap {

template< typename T, bool is_function_type = false >
                                   struct add_pointer              { typedef typename remove_reference<T>::type* type; };
template< typename T >             struct add_pointer<T, true>     { typedef T type; };
template< typename R, typename T1> struct add_pointer<R(T1), true> { typedef R(*type)(T1); };

} // namespace detail_ap

template< typename T > struct add_pointer : detail_ap::add_pointer<T, is_function<T>::value> {};

template< typename T > struct is_void : is_same<void, typename remove_cv<T>::type> {};

template< typename T >
struct decay
{
private:
    typedef typename remove_reference<T>::type U;
public:
    typedef typename conditional<
        is_array<U>::value,
        typename remove_extent<U>::type*,
        typename conditional<
            is_function<U>::value,
            typename add_pointer<U>::type,
            typename remove_cv<U>::type
        >::type
    >::type type;
};

template< typename F >              struct result_of;
template< typename R, typename T1 > struct result_of<R (*)(T1)> { typedef R type; };
template< typename R, typename T1 > struct result_of<R (&)(T1)> { typedef R type; };
template< typename R >              struct result_of<R (*)()>   { typedef R type; };
template< typename R >              struct result_of<R (&)()>   { typedef R type; };

}}} // namespace nonstd::optfun_lite::detail

//#endif // optfun_CPP11_OR_GREATER

//
// class monostate:
//

namespace nonstd { namespace optfun_lite {

class monostate {};

optfun_constexpr inline bool operator< ( monostate, monostate ) optfun_noexcept { return false; }
optfun_constexpr inline bool operator> ( monostate, monostate ) optfun_noexcept { return false; }
optfun_constexpr inline bool operator<=( monostate, monostate ) optfun_noexcept { return true;  }
optfun_constexpr inline bool operator>=( monostate, monostate ) optfun_noexcept { return true;  }
optfun_constexpr inline bool operator==( monostate, monostate ) optfun_noexcept { return true;  }
optfun_constexpr inline bool operator!=( monostate, monostate ) optfun_noexcept { return false; }

}} // namespace nonstd::optfun_lite

// specialize the std::hash algorithm:

#if optfun_CPP11_OR_GREATER

namespace std {

template<>
struct hash< ::nonstd::optfun_lite::monostate >
{
public:
    std::size_t operator()( ::nonstd::optfun_lite::monostate const & /*v*/ ) const optfun_noexcept
    {
        return 0;
    }
};

} //namespace std

#endif // optfun_CPP11_OR_GREATER

//
// functional algorithms:
//

namespace nonstd { namespace optfun_lite {

namespace detail {

#define optfun_mk_proxy( name )     \
    template< typename F >          \
    struct name                     \
    {                               \
        F f;                        \
        name( F f_ ) : f( f_ ) {}   \
    };

#define optfun_mk_proxy_arg( name )     \
    template< typename F, typename U >  \
    struct name                         \
    {                                   \
        F f; U const & u;               \
        name( F f_, U const & u_)       \
        : f( f_), u( u_) {}             \
    };

#define optfun_mk_proxy_fun( name )     \
    template< typename F, typename U >  \
    struct name                         \
    {                                   \
        F f; U u;                       \
        name( F f_, U u_)               \
        : f( f_), u( u_) {}             \
    };

optfun_mk_proxy(     map )
optfun_mk_proxy_arg( map_or )
optfun_mk_proxy_fun( map_or_else )
optfun_mk_proxy(     and_then    )
optfun_mk_proxy(     or_else     )
optfun_mk_proxy(     and_ )
optfun_mk_proxy(     or_ )
//optfun_mk_proxy(     take )

#undef optfun_mk_proxy
#undef optfun_mk_proxy_arg
#undef optfun_mk_proxy_fun

// map(f):
// - perform operation `U f(T)` on optional's content if present and return an optional<U>.
// - perform operation `void f(T)` on optional's content if present and return an optional<monostate>..

template< typename F, typename T, typename Enable = void >
struct map_t;

// map(f): perform operation `U f(T)` on optional's
// content if present and return an optional<U>.

template< typename F, typename T >
struct map_t<F, T, typename enable_if< ! is_void< optfun_RESULT_OF_T(F) >::value >::type >
{
    typedef optional< optfun_INVOKE_RESULT_T(F,T) > result_t;

    F f;

    map_t( map<F> proxy )
    : f( proxy.f ) {}

    result_t
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return optfun_INVOKE( f, o.value() );
        }
        return nonstd::nullopt;
    }

};

// map(f): perform operation `void f(T)` on optional's
// content if present and return an optional<monostate>.

template< typename F, typename T >
struct map_t<F, T, typename enable_if< is_void< optfun_RESULT_OF_T(F) >::value >::type >
{
    typedef optional< monostate > result_t;

    F f;

    map_t( map<F> proxy )
    : f( proxy.f ) {}

    result_t
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            optfun_INVOKE( f, o.value() );
            return monostate();
        }
        return nullopt;
    }
};

// map_or(f, u): perform operation `U f(T)` on optional's
// content if present and return it, otherwise return u.

template< typename F, typename T, typename U >
struct map_or_t
{
    typedef U result_t;

    F f;
    U const & u;

    map_or_t( map_or<F,U> proxy )
    : f( proxy.f ), u( proxy.u ) {}

    result_t
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return optfun_INVOKE( f, o.value() );
        }
        return u;
    }
};

// map_or_else(f, u): perform operation `U f(T)` on optional's
// content if present and return it, otherwise return operation u().

template< typename F, typename T, typename U >
struct map_or_else_t
{
    typedef optfun_RESULT_OF_T(U) result_t;

    F f;
    U u;

    map_or_else_t( map_or_else<F,U> proxy )
    : f( proxy.f ), u( proxy.u ) {}

    result_t
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return f( o.value() );
        }
        return u();
    }
};

// and_then(f): return operation `optional<U> f(T)` on optional's
// content if present and return an optional<U>.

template< typename F, typename T >
struct and_then_t
{
    typedef optional<T> result_t;

    F f;

    and_then_t( and_then<F> proxy )
    : f( proxy.f ) {}

    result_t operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return optfun_INVOKE( f, o.value() );
        }
        return nonstd::nullopt;
    }
};

// or_else(f):
// - return the call `R f()` if optional is empty, otherwise return optional.
// - call `void f()` and return nullopt if optional is empty, otherwise return optional.

template< typename F, typename T, typename Enable = void >
struct or_else_t;

// or_else(f): return the call `R f()` if optional is empty, otherwise return optional.

template< typename F, typename T >
struct or_else_t<F, T, typename enable_if< ! is_void< optfun_RESULT_OF_T(F) >::value >::type >
{
    typedef optional< optfun_RESULT_OF_T(F) > result_t;

    F f;

    or_else_t( or_else<F> proxy )
    : f( proxy.f ) {}

    result_t 
    operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return o;
        }
        return f();
    }
};

// or_else(f): call `void f()` and return nullopt if optional is empty, otherwise return optional.

template< typename F, typename T >
struct or_else_t<F, T, typename enable_if< is_void< optfun_RESULT_OF_T(F) >::value >::type >
{
    typedef optional<T> result_t;

    F f;

    or_else_t( or_else<F> proxy )
    : f( proxy.f ) {}

    result_t operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return o;
        }

        f();
        return nullopt;
    }
};

// and_(): return `u` if `*this` has a value, otherwise return an empty optional.

template< typename U, typename T >
struct and__t
{
    typedef optional<U> result_t;

    U u;

    and__t( and_<U> proxy )
    : u( proxy.f ) {}

    result_t operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return u;
        }
        return nullopt;
    }
};

// or_(): return the current value if non-empty, otherwise return `u`.

template< typename U, typename T >
struct or__t
{
    typedef U result_t;

    U u;

    or__t( or_<U> proxy )
    : u( proxy.f ) {}

    result_t operator()( optional<T> const & o ) const
    {
        if ( has_value( o ) )
        {
            return o.value();
        }
        return u;
    }
};

//// take(): Take the value out of the optional, leaving it empty and return it:
//
//optfun_f take()
//{
//    optfun_f result; result.swap( *this );
//    return result;
//}

} // namespace detail

// create the algorithm types:

#define optfun_mk_alg_alias( alias, name )  \
    template< typename F >                  \
    detail::name<F> alias( F f )            \
    {                                       \
        return detail::name<F>( f );        \
    }

#define optfun_mk_alg_arg_alias( alias, name )  \
    template< typename F, typename U >          \
    detail::name<F,U> alias( F f, U const & u ) \
    {                                           \
        return detail::name<F,U>( f, u );       \
    }

#define optfun_mk_alg_fun_alias( alias, name )  \
    template< typename F, typename U >          \
    detail::name<F,U> alias( F f, U u ) \
    {                                           \
        return detail::name<F,U>( f, u );       \
    }

#define optfun_mk_algorithm( name )         \
    optfun_mk_alg_alias( name, name )

#define optfun_mk_algorithm_arg( name )     \
    optfun_mk_alg_arg_alias( name, name )

#define optfun_mk_algorithm_fun( name )     \
    optfun_mk_alg_fun_alias( name, name )

optfun_mk_algorithm(     map )
optfun_mk_algorithm_arg( map_or )
optfun_mk_algorithm_fun( map_or_else )
optfun_mk_algorithm(     and_then )
optfun_mk_alg_alias(     then, and_then )
optfun_mk_algorithm(     or_else )
optfun_mk_algorithm(     and_ )
optfun_mk_algorithm(     or_ )
//optfun_mk_algorithm( take )

#undef optfun_mk_alg_alias
#undef optfun_mk_alg_arg_alias
#undef optfun_mk_alg_fun_alias
#undef optfun_mk_algorithm
#undef optfun_mk_algorithm_arg
#undef optfun_mk_algorithm_fun

// create the pipe operators:

#define optfun_mk_pipe( name )                      \
    template< typename T, typename F >              \
    typename detail::name##_t<F,T>::result_t        \
    operator|( optional<T> o, detail::name<F> f )   \
    {                                               \
        return detail::name##_t<F,T>( f )( o );     \
    }

#define optfun_mk_pipe_arg( name )                  \
    template< typename T, typename F, typename U >  \
    typename detail::name##_t<F,T,U>::result_t      \
    operator|( optional<T> o, detail::name<F,U> f ) \
    {                                               \
        return detail::name##_t<F,T,U>( f )( o );   \
    }

optfun_mk_pipe(     map )
optfun_mk_pipe_arg( map_or )
optfun_mk_pipe_arg( map_or_else )
optfun_mk_pipe(     and_then )
optfun_mk_pipe(     or_else )
optfun_mk_pipe(     and_ )
optfun_mk_pipe(     or_ )
//optfun_mk_pipe( take )

#undef optfun_mk_pipe
#undef optfun_mk_pipe_arg

}} // namespace nonstd::optfun_lite

//
// make algorithms available in namespace nonstd:
//

namespace nonstd {

using optfun_lite::map;
using optfun_lite::map_or;
using optfun_lite::map_or_else;
using optfun_lite::then;
using optfun_lite::and_then;
using optfun_lite::or_else;
using optfun_lite::and_;
using optfun_lite::or_;
//using optfun_lite::take;

using optfun_lite::operator|;

} // namespace nonstd

#endif // optfun_CPP17_OR_GREATER

#endif // NONSTD_OPTIONAL_FUN_LITE_HPP
