cmake_minimum_required(VERSION 2.8)

project(nono)

find_package(PkgConfig)

#pkg_check_modules(GTKMM gtkmm-2.4)
#pkg_check_modules(GLIBMM glibmm-2.4)
#pkg_check_modules(GTK_PLUS gtk+-2.0)
#pkg_check_modules(GDK_PIXBUF gdk-pixbuf-2.0)
#pkg_check_modules(GIOMM giomm-2.4)
#pkg_check_modules(GDKMM gdkmm-2.4)
pkg_check_modules(CURL libcurl)
pkg_check_modules(JSONCPP jsoncpp)

set(COMMON_FLAGS
  "-I .. -std=c++0x -pthread -Wall -Wextra -Wfloat-equal -Wno-unused-result -Wshadow -Wstrict-aliasing"
)

set(OPTIMISE_FLAGS
  "-pipe -msse2 -fforce-addr -ftree-vectorize -funroll-loops"
)


set(DEBUG_FLAGS
  "${COMMON_FLAGS} -g"
)

set(OPTIMISED_DEBUG_FLAGS
  "${COMMON_FLAGS} ${OPTIMISE_FLAGS} -g -O2" 
)

set(OPTIMISING_FLAGS
  "${COMMON_FLAGS} ${OPTIMISE_FLAGS} -DNDEBUG -O3" 
)

set(CMAKE_CXX_FLAGS 
  ${OPTIMISING_FLAGS}
  #${OPTIMISED_DEBUG_FLAGS}
  #${DEBUG_FLAGS}
) 

#include_directories("/usr/include")
include_directories(${CURL_INCLUDE_DIRS})
  
include_directories(${JSONCPP_INCLUDE_DIRS})



file(GLOB SOURCE_FILES
    "*.cpp"
    "*/*.cpp"
)

add_executable(../nono
  ${SOURCE_FILES}
)

target_link_libraries(../nono
 ${CURL_LIBRARIES}
 ${JSONCPP_LIBRARIES}
)
