add_library(geoip2 SHARED
    ${CMAKE_CURRENT_LIST_DIR}/data-pool.c
    ${CMAKE_CURRENT_LIST_DIR}/maxminddb.c
    ${CMAKE_CURRENT_LIST_DIR}/extension.cpp
    ${CMAKE_CURRENT_LIST_DIR}/geoip_util.cpp
)

target_include_directories(geoip2 PUBLIC
    ./
)


target_link_libraries(geoip2 PUBLIC amsdk)

#if (WIN32)
#    target_link_libraries(geoip2 PRIVATE ws2_32)
#endif()
set_target_properties(geoip2 PROPERTIES PREFIX "" SUFFIX ".ext${LIB_SHARED_EXT}")