#          Copyright Marc Bodmer 2016-2016.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.6)

add_executable(basic_tests
  basic_tests.cpp
)

target_include_directories(basic_tests
  SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(basic_tests
  PROPERTIES CXX_STANDARD 14
)

#target_compile_features(basic_tests
#  PRIVATE cxx_constexpr
#)

#target_link_libraries(basic_tests

#)
