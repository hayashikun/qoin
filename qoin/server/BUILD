load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello_server",
    srcs = ["hello_server.cc"],
    deps = [
        "//qoin/proto:hello_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)


cc_binary(
    name = "face_mesh_server",
    srcs = ["face_mesh_server.cc"],
    deps = [
        "//qoin/proto:face_mesh_cc_grpc",
        "//qoin/solution:solution",
        "@com_github_grpc_grpc//:grpc++",
        "@mediapipe//mediapipe/graphs/face_mesh:desktop_live_calculators",
    ],
)
