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

# Needed for Pyx Integration only
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../Pyx/Pyx)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../Pyx.BDO/Sources/PyxBDO/json)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../Pyx/x64/Release)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../MyAStar/build/Src/Release)

add_library(PyxMyAStarLib ${SOURCE} ${HEADERS} PyxMyAStar.cpp PyxMyAStar.h)
add_library(MyAStar ${SOURCE} ${HEADERS})
add_executable(MyAStartest test.cpp)
target_link_libraries(MyAStartest MyAStar)


