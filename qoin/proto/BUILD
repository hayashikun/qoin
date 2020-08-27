load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_google_protobuf//:protobuf.bzl", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "hello_proto",
    srcs = ["hello.proto"],
)

cc_proto_library(
    name = "hello_cc_proto",
    srcs = ["hello.proto"],
)

cc_grpc_library(
    name = "hello_cc_grpc",
    srcs = [":hello_proto"],
    grpc_only = True,
    deps = [":hello_cc_proto"],
)

proto_library(
    name = "face_mesh_proto",
    srcs = ["face_mesh.proto"],
    deps = [
        "@mediapipe//mediapipe/framework/formats:landmark_proto",
    ],
)

cc_proto_library(
    name = "face_mesh_cc_proto",
    srcs = ["face_mesh.proto"],
    deps = [
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
)

cc_grpc_library(
    name = "face_mesh_cc_grpc",
    srcs = [":face_mesh_proto"],
    grpc_only = True,
    deps = [":face_mesh_cc_proto"],
)

proto_library(
    name = "hand_tracking_proto",
    srcs = ["hand_tracking.proto"],
    deps = [
        "@mediapipe//mediapipe/framework/formats:detection_proto",
        "@mediapipe//mediapipe/framework/formats:landmark_proto",
    ],
)

cc_proto_library(
    name = "hand_tracking_cc_proto",
    srcs = ["hand_tracking.proto"],
    deps = [
        "@mediapipe//mediapipe/framework/formats:detection_cc_proto",
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
)

cc_grpc_library(
    name = "hand_tracking_cc_grpc",
    srcs = [":hand_tracking_proto"],
    grpc_only = True,
    deps = [":hand_tracking_cc_proto"],
)
