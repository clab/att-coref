PROJECT(cnn:parser)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_EXECUTABLE(att-coref main.cc)
target_link_libraries(att-coref cnn ${Boost_LIBRARIES})

