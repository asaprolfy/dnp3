cmake_minimum_required (VERSION 3.0)
project (dnp3hammer VERSION 1.0.0)

# other options off-by-default that you can enable
option(COVERAGE "Builds the libraries with coverage info for gcov" OFF)

# PkgConfig
FIND_PACKAGE(PkgConfig) # tell cmake to require pkg-config
PKG_CHECK_MODULES(GLIB2 REQUIRED glib-2.0>=2.36.0)

set(LIB_TYPE STATIC)

set(CMAKE_C_FLAGS "-Wall -std=c99 -D_POSIX_C_SOURCE=2  -D_DARWIN_C_SOURCE=900000L -I/usr/local/include -L/usr/local/lib -L/opt/homebrew/Cellar/glib/2.80.0_2/lib -L/opt/homebrew/opt/gettext/lib")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -I/usr/local/include -L/usr/local/lib -L/opt/homebrew/Cellar/glib/2.80.0_2/lib -L/opt/homebrew/opt/gettext/lib")

if(COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
endif()

# different release and debug flags
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

# include paths for all the local libraries
include_directories(include)

# for the tests
# TODO - only add these for the required test projects
include_directories(${GLIB2_INCLUDE_DIRS})
include_directories(test/catch)

# ---- parser library ----
file(GLOB_RECURSE dnp3hammer_SRC src/*.c)
add_library(dnp3hammer ${LIB_TYPE} ${dnp3hammer_SRC})
target_link_libraries(dnp3hammer hammer)

# ---- unit test suite ----
add_executable(dnp3-tests ./test/unit/main.c)
target_link_libraries(dnp3-tests dnp3hammer ${GLIB2_LIBRARIES})

# ---- plugin test suite ----
file(GLOB_RECURSE plugintests_SRC test/plugin/*.cpp)
add_executable(plugin-tests ${plugintests_SRC} test/plugin/fixtures/DNP3Helpers.h)
target_link_libraries(plugin-tests dnp3hammer)

# ---- crc example program -----
add_executable(crc crc.c)
target_link_libraries(crc dnp3hammer)

# ---- dissect example program -----
add_executable(dissect dissect.c)
target_link_libraries(dissect dnp3hammer)
