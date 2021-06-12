cmake_minimum_required(VERSION 3.15)
project(Part1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Part1 main.cpp universalMutex.cpp universalMutex.h universalThread.cpp universalThread.h universalFunctions.cpp universalFunctions.h universalBarrier.cpp universalBarrier.h universalSemaphore.cpp universalSemaphore.h universalPool.cpp universalPool.h universalCondition.cpp universalCondition.h universalAsync.cpp universalAsync.h universalFuture.cpp universalFuture.h)