
::set optional=^<boost\optional.hpp^>
::set include=D:\Own\Martin\Local\Work\Client\IP\Project\Camera\Vendor\boost_1_59_0

set optionalx=^<optional^>
set include=""

cl -W3 -EHsc -std:c++17 -Doptfun_OPTIONAL_HEADER=^<optional^> -I"%include%" -I../include/nonstd optional-fun-main.t.cpp optional-fun.t.cpp && optional-fun-main.t.exe

