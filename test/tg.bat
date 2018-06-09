@setlocal
@set std=%1
@if "%std%"=="" set std=c++11
g++ -std=%std% -O2 -Wall -Wextra -Wno-unused-parameter -Doptfun_OPTIONAL_HEADER=\"../../optional-lite/include/nonstd/optional.hpp\" -I../include/nonstd optional-fun-main.t.cpp optional-fun.t.cpp && optional-fun-main.t.exe
@endlocal

