
file(GLOB_RECURSE  SOURCES *.h *.cc)

add_library(base STATIC ${SOURCES})
target_link_libraries(
        base
        glog
        gflags
        boost_system
        pthread)
