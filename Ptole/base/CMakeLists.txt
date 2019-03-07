set(BASE_SRCS
ThreadPool.cpp
Thread.cpp
)
add_library(Ptole_base ${BASE_SRCS})
target_link_libraries(Ptole_base pthread)
add_subdirectory(test)