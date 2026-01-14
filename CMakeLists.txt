cmake_minimum_required(VERSION 3.18)

project(SimpleVCPKGTest CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

# Should be using C++17, maybe 20 now
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FIND_PACKAGE(PNG REQUIRED)
if(PNG_FOUND)
  message(STATUS "PNG Version: ${PNG_VERSION_STRING}, Includes: ${PNG_INCLUDE_DIR}, Libs: ${PNG_LIBRARIES}")
  include_directories(${PNG_INCLUDE_DIR})
else(PNG_FOUND)
  message(STATUS "Could not find the PNG Libraries!")
endif(PNG_FOUND)

Include(FetchContent)

# 
# Catch2 for UnitTesting with C++
#
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_executable(main
	main.cpp)

#
# Unit Tests - by enabling testing with cmake, we can create a target that lets unit tests be run. After re-building
# yourproject with ENABLE_TESTING called, a make target, called test will be enabled. You can then type
#
# make test
#
# to perform the unit tests. See the CMakeLists.txt file in the utests directory for more details. Also, see the unit
# test .cpp files in the utests directory for examples on using Boost's unit test system.
#

enable_testing()
include(CTest)
include(Catch)

set(UTESTS
    test_example)

foreach(uexec ${UTESTS})
  add_executable(${uexec} ${BUNDLEOPTS} tests/${uexec}.cpp)

  target_link_libraries(${uexec} PRIVATE Catch2::Catch2WithMain)

  catch_discover_tests(${uexec})
endforeach(uexec)
