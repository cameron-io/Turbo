cmake_minimum_required(VERSION 3.31 FATAL_ERROR)
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif ()
project(turbo VERSION 0.1.0 LANGUAGES C CXX)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS true)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static_lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}/bin")

include(FetchContent)

include_directories(.)

###
# Dependencies
###

set(Boost_INCLUDE_LIBRARIES math)
set(Boost_ENABLE_CMAKE ON)
set(Boost_USE_MULTITHREADED ON)
# # whether to force the use of the static libraries
# set(Boost_USE_STATIC_LIBS OFF)
# # whether to use libraries linked statically to the C++ runtime ("s" tag)
# set(Boost_USE_STATIC_RUNTIME OFF)
include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.87.0
)
FetchContent_MakeAvailable(Boost)

###
# Libraries
###

# table_lib

add_library(table_lib SHARED lib/tables/hash_table.cpp
)
add_executable(hash_table_tests tests/tables/hash_table_tests.cpp)
target_link_libraries(hash_table_tests table_lib Boost::assert)
add_test(NAME hash_table_tests COMMAND hash_table_tests)

# linked_list_lib

add_library(linked_list_lib SHARED
    lib/linked_lists/queue.hpp
    lib/linked_lists/stack.hpp)
set_target_properties(linked_list_lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(queue_tests tests/linked_lists/queue_tests.cpp)
target_link_libraries(queue_tests linked_list_lib)
add_test(NAME queue_tests COMMAND queue_tests)

add_executable(stack_tests tests/linked_lists/stack_tests.cpp)
target_link_libraries(stack_tests linked_list_lib)
add_test(NAME stack_tests COMMAND stack_tests)

# oop_lib

add_library(oop_lib SHARED
    lib/oop/design_patterns/singleton.hpp
    lib/oop/polymorphism.hpp
    lib/oop/object_copy.hpp)
set_target_properties(oop_lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(object_copy_tests tests/oop/object_copy_tests.cpp)
target_link_libraries(object_copy_tests oop_lib)
add_test(NAME object_copy_tests COMMAND object_copy_tests)

add_executable(polymorphism_tests tests/oop/polymorphism_tests.cpp)
target_link_libraries(polymorphism_tests oop_lib)
add_test(NAME polymorphism_tests COMMAND polymorphism_tests)

add_executable(singleton_tests tests/oop/singleton_tests.cpp)
target_link_libraries(singleton_tests oop_lib Boost::assert)
add_test(NAME singleton_tests COMMAND singleton_tests)

# builder_lib

add_library(builder_lib SHARED
    lib/oop/design_patterns/builder/CarProduct.hpp
    lib/oop/design_patterns/builder/ICarBuilder.hpp
    lib/oop/design_patterns/builder/Pipeline.hpp
    lib/oop/design_patterns/builder/SportsCarBuilder.hpp)
    
set_target_properties(builder_lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(builder_pattern_tests tests/oop/builder_pattern_tests.cpp)
target_link_libraries(builder_pattern_tests builder_lib Boost::assert)
add_test(NAME builder_pattern_tests COMMAND builder_pattern_tests)

# factory_lib

add_library(factory_lib SHARED
    lib/oop/design_patterns/factory/domain/IAccount.hpp
    lib/oop/design_patterns/factory/domain/IAccountFactory.hpp
    lib/oop/design_patterns/factory/application/AccountBusiness.hpp
    lib/oop/design_patterns/factory/application/AccountPersonal.hpp
    lib/oop/design_patterns/factory/service/AccountBusinessCreator.hpp
    lib/oop/design_patterns/factory/service/AccountPersonalCreator.hpp
)

set_target_properties(factory_lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(factory_tests tests/oop/factory_tests.cpp)
target_link_libraries(factory_tests factory_lib Boost::assert)
add_test(NAME factory_tests COMMAND factory_tests)

# dependency_injection_tests

add_library(dependency_injection_lib SHARED
    lib/oop/design_patterns/dependency_injection/Car.hpp
    lib/oop/design_patterns/dependency_injection/EnergySource.hpp
    lib/oop/design_patterns/dependency_injection/EnergySourceBattery.hpp
    lib/oop/design_patterns/dependency_injection/EnergySourcePetrol.hpp)
    
set_target_properties(dependency_injection_lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(dependency_injection_tests tests/oop/dependency_injection_tests.cpp)
target_link_libraries(dependency_injection_tests dependency_injection_lib)
add_test(NAME dependency_injection_tests COMMAND dependency_injection_tests)

add_executable(interface_tests tests/oop/interface_tests.cpp)
target_link_libraries(interface_tests dependency_injection_lib)
add_test(NAME interface_tests COMMAND interface_tests)

# multi_threading_lib

add_library(multi_threading_lib SHARED lib/multi_threading/parallelism.hpp)
set_target_properties(multi_threading_lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(multi_threading_tests tests/multi_threading/parallelism_tests.cpp)
add_test(NAME multi_threading_tests COMMAND multi_threading_tests)
target_sources(multi_threading_tests PRIVATE lib/multi_threading/parallelism.cpp)

# fibonacci_lib

add_library(fibonacci_lib SHARED lib/dynamic_programming/fibonacci.hpp)
set_target_properties(fibonacci_lib PROPERTIES LINKER_LANGUAGE CXX)

add_executable(dynamic_programming_tests tests/dynamic_programming/fibonacci_tests.cpp)
target_link_libraries(dynamic_programming_tests fibonacci_lib Boost::assert)
add_test(NAME dynamic_programming_tests COMMAND dynamic_programming_tests)

# pointer_arithmetic

add_executable(pointer_arithmetic_tests tests/memory/pointer_arithmetic_tests.cpp)
add_test(NAME pointer_arithmetic_tests COMMAND pointer_arithmetic_tests)

# type_punning

add_executable(type_punning_tests tests/types/type_punning_tests.cpp)
target_link_libraries(type_punning_tests Boost::assert)
add_test(NAME type_punning_tests COMMAND type_punning_tests)

###
# CTest
###

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
