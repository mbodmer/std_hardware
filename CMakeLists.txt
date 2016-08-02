#          Copyright Marc Bodmer 2016-2016.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#        http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# export compilation database: compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

project(std_hardware VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(tests/basic_tests)
