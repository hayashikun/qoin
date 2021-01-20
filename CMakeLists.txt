cmake_minimum_required(VERSION 3.17)
project(qoin)

set(CMAKE_CXX_STANDARD 14)

include_directories(bazel-bin/external/mediapipe)
include_directories(bazel-qoin/external/mediapipe)
include_directories(bazel-qoin/external/com_github_grpc_grpc/include)
include_directories(bazel-qoin/external/com_google_absl)
include_directories(bazel-bin/external/com_github_gflags_gflags/_virtual_includes/gflags)
include_directories(bazel-qoin/external/macos_opencv/include)
include_directories(bazel-bin/external/com_github_glog_glog/_virtual_includes/default_glog_headers)
include_directories(bazel-qoin/external/com_google_protobuf/src)
include_directories(bazel-bin)
include_directories(.)

add_executable(qoin
        qoin/client/face_mesh_client.cc
        qoin/client/hand_tracking_client.cc
        qoin/client/grpc_client.cc
        qoin/hello_world/hello_world.cc
        qoin/server/face_mesh_server.cc
        qoin/server/hand_tracking_server.cc
        qoin/server/hello_server.cc
        qoin/solution/face_mesh.cc
        qoin/solution/hand_tracking.cc
        qoin/solution/solution.cc
        )
