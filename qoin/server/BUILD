load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello_server",
    srcs = ["hello_server.cc"],
    deps = [
        "//qoin/proto:hello_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
