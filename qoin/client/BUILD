load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")


cc_library(
    name = "grpc_client",
    srcs = ["grpc_client.cc"],
    hdrs = ["grpc_client.h"],
    deps = [
        "@com_github_glog_glog//:glog",
        "@com_github_grpc_grpc//:grpc++",
    ]
)

cc_binary(
    name = "face_mesh",
    srcs = ["face_mesh_client.cc"],
    deps = [
        ":grpc_client",
        "//qoin/proto:face_mesh_cc_grpc",
        "//qoin/solution:solution",
        "@mediapipe//mediapipe/graphs/face_mesh:desktop_live_calculators",
    ],
)

cc_binary(
    name = "hand_tracking",
    srcs = ["hand_tracking_client.cc"],
    deps = [
        ":grpc_client",
        "//qoin/proto:hand_tracking_cc_grpc",
        "//qoin/solution:solution",
        "@mediapipe//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
    ],
)