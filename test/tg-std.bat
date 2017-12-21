
::set optional=^<boost\optional.hpp^>
::set include=D:\Own\Martin\Local\Work\Client\IP\Project\Camera\Vendor\boost_1_59_0

set optional=^<optional^>
set include=""

g++ -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -Doptfun_OPTIONAL_HEADER="%optional%" -I"%include%" -o optional-fun-lite.t.exe -I../include/nonstd optional-fun-lite.t.cpp optional-fun.t.cpp && optional-fun-lite.t.exe
