PROJECT (xt)

find_package(Boost REQUIRED COMPONENTS regex)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8) # fucking piece of shit of a build system shut the fuck up

if (UNIX)
	add_definitions(-Wall -g -DUNIX -lc_g)
else (UNIX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
endif (UNIX)

set (SOURCES object seq vector list persistent_arraymap main)

set_source_files_properties(${SOURCES} PROPERTIES COMPILE_FLAGS "-std=c++0x")

add_executable(xtc ${SOURCES})

