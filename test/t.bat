@setlocal
@set std=%1
@if not "%std%"=="" set std=-std:%std%
cl -W3 -EHsc %std% -Doptfun_OPTIONAL_HEADER=\"../../optional-lite/include/nonstd/optional.hpp\" -I../include/nonstd optional-fun-lite.t.cpp optional-fun.t.cpp && optional-fun-lite.t.exe
@endlocal

