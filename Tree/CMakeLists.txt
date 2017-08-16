set(TREE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Tree/Sources)

file(GLOB TREE_SOURCES
  ${TREE_SOURCE_DIR}/*.cpp
  ${TREE_SOURCE_DIR}/*.h
  ${TREE_SOURCE_DIR}/*.inl)

add_definitions(-DBOOST_ALL_NO_LIB)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost COMPONENTS program_options)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_library(Tree STATIC ${TREE_SOURCES})
  target_link_libraries(Tree ${Boost_LIBRARIES})
endif()


