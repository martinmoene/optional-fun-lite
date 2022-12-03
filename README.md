# optional-fun lite: C++23's monadic operations of optional for C++98 and later

This library is still under (unintense) development.

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17/20/23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://github.com/martinmoene/optional-fun-lite/actions/workflows/ci.yml/badge.svg)](https://github.com/martinmoene/optional-fun-lite/actions/workflows/ci.yml) [![Build status](https://ci.appveyor.com/api/projects/status/nrnbfhvvp39ex075?svg=true)](https://ci.appveyor.com/project/martinmoene/optional-fun-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Foptional-fun-lite.svg)](https://github.com/martinmoene/optional-fun-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/optional-fun-lite/master/include/nonstd/optional-fun.hpp) <!--[![Conan](https://img.shields.io/badge/on-conan-blue.svg)](URL)--> [![Try it online](https://img.shields.io/badge/on-wandbox-blue.svg)](URL) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](URL)

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Other implementations](#other-implementations)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

<!-- - [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests) -->

## Example usage

```Cpp
#include "nonstd/optional-fun.hpp"
#include <iostream>

int main(int argc, char **)
{
}
```

### Compile and run

```Text
$ g++ -std=c++11 -Wall -I../include/ -o main.exe main.cpp && main.exe
```

## In a nutshell

**optional-fun lite** is a single-file header-only library to provide [C++23 monadic operations]() to [C++17's class optional](https://en.cppreference.com/w/cpp/utility/optional) for use with C++98 and later. 
<!-- If available, the standard library is used, unless [configured](#configuration) otherwise. -->

Currently this library does not (yet) support ... .

**Features and properties of optional-fun lite** are ease of installation (single header), freedom of dependencies other than the standard library.

**Limitations of optional-fun lite** are ... \[*to be summed up*\].

## License

*optional-fun lite* is distributed under the [Boost Software License](https://github.com/martinmoene/optional-fun-lite/blob/master/LICENSE.txt).

## Dependencies

*optional-fun lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation

*optional-fun lite* is a single-file header-only library. Put `optional-fun.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

- [Documentation of `class optional-fun`](#documentation-of-class-optional-fun)
- [*optional-fun lite* implementation status](#optional-fun-lite-implementation-status)
- [Configuration](#configuration)

### Documentation of class optional-fun

\[*Envisioned*\] Depending on the compiler and C++ standard used, *optional-fun lite* behaves less or more like the standard's version. To get an idea of the capabilities of *optional-fun lite* with your configuration, look at the output of the [tests](test/optional-fun.t.cpp), issuing `optional-fun-main.t --pass @`.

For the standard's documentation, see section *Member functions, Monadic operations* of [`class optional`](https://en.cppreference.com/w/cpp/utility/optional), which is part of the [C++ Utility library](https://en.cppreference.com/w/cpp/utility).

### *optional-fun lite* implementation status

| Kind               | Type or function             | Notes |
|--------------------|------------------------------|-------|
| &nbsp;             | &nbsp; | &nbsp; |

### Configuration

<!--
#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *optional-fun lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/optional-fun.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define optional-fun_CPLUSPLUS 201103L`.
-->

<!--
#### Select `std::optional-fun` or `nonstd::optional-fun`

\[*To be implemented*\]

At default, *optional-fun lite* uses `std::optional-fun` if it is available and lets you use it via namespace `nonstd`. You can however override this default and explicitly request to use `std::optional-fun` or optional-fun lite's `nonstd::optional-fun` as `nonstd::optional-fun` via the following macros.

-D<b>optional-fun\_CONFIG\_SELECT\_XXX</b>=optional-fun\_SELECT\_XXX\_NONSTD  
Define this to `optional-fun__CONFIG_SELECT_XXX_STD` to select `std::optional-fun` as `nonstd::optional-fun`. Define this to `optional-fun_SELECT_XXX_NONSTD` to select `nonstd::optional-fun` as `nonstd::optional-fun`. Default is undefined, which has the same effect as defining to `optional-fun_SELECT_XXX_NONSTD` currently (this may change to `optional-fun_SELECT_XXX_DEFAULT`).
-->

<!--
#### Standard selection macro

\-D<b>optional-fun\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.
-->

<!--
#### Disable exceptions

-D<b>optional-fun_CONFIG_NO_EXCEPTIONS</b>=0
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined.
-->

## Other implementations

- [optional]([url](https://github.com/TartanLlama/optional)). C++11/14/17 std::optional with functional-style extensions and reference support. Simon Brand.

## Notes and references

[1] CppReference. [Optional](http://en.cppreference.com/w/cpp/utility/optional).

[2] ISO/IEC WG21. [Draft 2022-11-11, section 22.5 Optional objects](https://eel.is/c++draft/optional). 2022.

[3] ISO/IEC WG21. [Draft 2022-11-11, section 22.5.3.7 Optional objects, Monadic operations](https://eel.is/c++draft/optional.monadic). 2022.

[4] Simon Brand. [p0798](http://wg21.link/p0798) - Monadic operations for std::optional. 2019.

## Appendix

<a id="a1"></a>
### A.1 Compile-time information

The version of *optional-fun lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

<a id="a2"></a>
### A.2 Optional-fun lite test specification

<details>
<summary>click to expand</summary>
<p>

```Text
optional-fun.t.cpp(28): passed: optional map(f): non-void[functional]: 2*v == (optional<int>(v) | map( double_int )).value() for 42 == 42
optional-fun.t.cpp(41): passed: optional map(f): void[functional]: monostate() == (optional<int>(v) | map( voider_int )).value() for [monostate] == [monostate]
optional-fun.t.cpp(50): passed: optional map_or(f): [functional]: 14 == (optional<int>( 7 ) | map_or( double_int, 42 )) for 14 == 14
optional-fun.t.cpp(51): passed: optional map_or(f): [functional]: 42 == (optional<int>( ) | map_or( double_int, 42 )) for 42 == 42
optional-fun.t.cpp(58): passed: optional map_or_else(f): [functional]: 14 == (optional<int>( 7 ) | map_or_else( double_int, seven )) for 14 == 14
optional-fun.t.cpp(59): passed: optional map_or_else(f): [functional]: 7 == (optional<int>( ) | map_or_else( double_int, seven )) for 7 == 7
optional-fun.t.cpp(69): passed: optional and_then(f): success[functional]: 2*v == (optional<int>(v) | then( double_opt )).value() for 42 == 42
optional-fun.t.cpp(70): passed: optional and_then(f): success[functional]: 2*v == (optional<int>(v) | and_then( double_opt )).value() for 42 == 42
optional-fun.t.cpp(78): passed: optional and_then(f): fail[functional]: ! ( (optional<int>(7) | and_then( double_opt ) | and_then( fail_opt ) | and_then( double_opt )).has_value() ) for ! ( false )
optional-fun.t.cpp(86): passed: optional or_else(f): non-void[functional]: -1 == (optional<int>(-1) | or_else( fun_or_else_nonvoid )).value() for -1 == -1
optional-fun.t.cpp(87): passed: optional or_else(f): non-void[functional]: fun_or_else_nonvoid() == (optional<int>( ) | or_else( fun_or_else_nonvoid )).value() for 7 == 7
optional-fun.t.cpp(92): passed: optional or_else(f): void[functional]: -1 == (optional<int>(-1) | or_else( fun_or_else_void )).value() for -1 == -1
optional-fun.t.cpp(93): passed: optional or_else(f): void[functional]: ! ( (optional<int>( ) | or_else( fun_or_else_void )).has_value() ) for ! ( false )
optional-fun.t.cpp(98): passed: optional and_(u): [functional]: 42 == (optional<int>(7) | and_( 42 )).value() for 42 == 42
optional-fun.t.cpp(99): passed: optional and_(u): [functional]: ! ( (optional<int>( ) | and_( 42 )).has_value() ) for ! ( false )
optional-fun.t.cpp(104): passed: optional or_(rhs): [functional]: 7 == (optional<int>(7) | or_( 42 )) for 7 == 7
optional-fun.t.cpp(105): passed: optional or_(rhs): [functional]: 42 == (optional<int>( ) | or_( 42 )) for 42 == 42
```

</p>
</details>
