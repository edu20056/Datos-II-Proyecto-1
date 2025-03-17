cmake_minimum_required(VERSION 3.28)
project(mptr-mem-mgr) # MPointers(mptr) : Memory Manager(mem-mgr)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_library(protolib proto/system.proto)
target_link_libraries(protolib gRPC::grpc++)

target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

protobuf_generate(TARGET protolib LANGUAGE cpp)

protobuf_generate(TARGET protolib LANGUAGE grpc 
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc 
PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

add_executable(mem-mgr src/mem-mgr.cc)
target_link_libraries(mem-mgr protolib)

add_executable(mptr src/mptr.cc)
target_link_libraries(mptr protolib)