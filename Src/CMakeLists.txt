SET(SOURCE
  MyAStar.cpp 
  MyNode.cpp
MyConnection.cpp
MyGraph.cpp
MyHeuristics.cpp
)

SET(HEADERS
MyNode.h
MyAStar.h
MyConnection.h
MyGraph.h
MyHeuristics.h
)

add_library(MyAStar ${SOURCE} ${HEADERS})
add_executable(MyAStartest test.cpp)
target_link_libraries(MyAStartest MyAStar)