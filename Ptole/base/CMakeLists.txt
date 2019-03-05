set(BASE_SRC
LoopThread.cpp
ThreadPool.cpp
Thread.cpp
)
add_library(Ptole_base BASE_SRC)
add_sub_directory(test)