add_subdirectory(3rdparty/libmaxminddb)

add_library(geoip2 SHARED
    ${CMAKE_CURRENT_LIST_DIR}/extension.cpp
    
)

target_include_directories(geoip2 PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

if (MSVC)
    # maxminddb specific.
    # SHIT, why this stupid pollute compile environment.
    add_definitions(-DBUILD_TESTING=OFF)
    target_compile_options(maxminddb PRIVATE /wd4068 /wd4090)
endif()

target_link_libraries(geoip2 PUBLIC amsdk maxminddb)
set_target_properties(geoip2 PROPERTIES PREFIX "" SUFFIX ".ext${LIB_SHARED_EXT}")
