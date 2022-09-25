cmake_minimum_required(VERSION 3.0)
project(dbus-c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)
include_directories(${DBUS_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})

add_executable(dbus-example dbus-example.c)
target_link_libraries(dbus-example ${DBUS_LIBRARIES})

add_executable(send send.c)
target_link_libraries(send ${DBUS_LIBRARIES})
