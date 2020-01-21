cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4_Jenny_Yael main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.cpp ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.cpp Solver.h CacheManager.cpp CacheManager.h FileCacheManager.cpp FileCacheManager.h StringReverser.cpp StringReverser.h Searchable.cpp Searchable.h Searcher.cpp Searcher.h ObjectAdapter.cpp ObjectAdapter.h State.cpp State.h Matrix.cpp Matrix.h BFS.cpp BFS.h DFS.cpp DFS.h Astar.cpp Astar.h BestFirstSearch.cpp BestFirstSearch.h Point.cpp Point.h)