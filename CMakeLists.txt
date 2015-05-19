project(market)

set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -std=c++11")
add_executable(market c_market.cpp c_user.cpp main.cpp)

