load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "client",
    srcs = ["client.cc"],
    deps = [
        "//qoin/proto:hello_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [
        "//qoin/proto:hello_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
