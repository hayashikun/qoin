workspace(name = "qoin")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

"""
http_archive(
    name = "mediapipe",
    strip_prefix = "mediapipe-master",
    urls = ["https://github.com/google/mediapipe/archive/master.zip"],
)
"""

local_repository(
    name = "mediapipe",
    path = "../mediapipe"
)

http_archive(
    name = "com_github_glog_glog",
    strip_prefix = "glog-3ba8976592274bc1f907c402ce22558011d6fc5e",
    sha256 = "feca3c7e29a693cab7887409756d89d342d4a992d54d7c5599bebeae8f7b50be",
    urls = [
        "https://github.com/google/glog/archive/3ba8976592274bc1f907c402ce22558011d6fc5e.zip",
    ],
)

http_archive(
    name = "com_google_protobuf",
    sha256 = "a79d19dcdf9139fa4b81206e318e33d245c4c9da1ffed21c87288ed4380426f9",
    strip_prefix = "protobuf-3.11.4",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.11.4.tar.gz"],
    patches = [
        "@mediapipe//third_party:com_google_protobuf_fixes.diff"
    ],
    patch_args = [
        "-p1",
    ],
)

http_archive(
    name = "build_bazel_rules_apple",
    sha256 = "7a7afdd4869bb201c9352eed2daf37294d42b093579b70423490c1b4d4f6ce42",
    url = "https://github.com/bazelbuild/rules_apple/releases/download/0.19.0/rules_apple.0.19.0.tar.gz",
    patches = [
        "@mediapipe//third_party:build_bazel_rules_apple_bypass_test_runner_check.diff"
    ],
    patch_args = [
        "-p1",
    ],
)

load(
    "@build_bazel_rules_apple//apple:repositories.bzl",
    "apple_rules_dependencies",
)

apple_rules_dependencies()

http_archive(
    name = "build_bazel_apple_support",
    sha256 = "122ebf7fe7d1c8e938af6aeaee0efe788a3a2449ece5a8d6a428cb18d6f88033",
    urls = [
        "https://storage.googleapis.com/mirror.tensorflow.org/github.com/bazelbuild/apple_support/releases/download/0.7.1/apple_support.0.7.1.tar.gz",
        "https://github.com/bazelbuild/apple_support/releases/download/0.7.1/apple_support.0.7.1.tar.gz",
    ],
)

http_archive(
    name = "com_google_absl",
    urls = [
        "https://github.com/abseil/abseil-cpp/archive/20200225.tar.gz",
    ],
    # Remove after https://github.com/abseil/abseil-cpp/issues/326 is solved.
    patches = [
        "@mediapipe//third_party:com_google_absl_f863b622fe13612433fdf43f76547d5edda0c93001.diff"
    ],
    patch_args = [
        "-p1",
    ],
    strip_prefix = "abseil-cpp-20200225",
    sha256 = "728a813291bdec2aa46eab8356ace9f75ac2ed9dfe2df5ab603c4e6c09f1c353"
)

# Required by glog
http_archive(
    name = "com_github_gflags_gflags",
    strip_prefix = "gflags-2.2.2",
    sha256 = "19713a36c9f32b33df59d1c79b4958434cb005b5b47dc5400a7a4b078111d9b5",
    url = "https://github.com/gflags/gflags/archive/v2.2.2.zip",
)

## Required by protobuf
http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.2/rules_python-0.0.2.tar.gz",
    strip_prefix = "rules_python-0.0.2",
    sha256 = "b5668cde8bb6e3515057ef465a35ad712214962f0b3a314e551204266c7be90c",
)

http_archive(
    name = "zlib",
    build_file = "@com_google_protobuf//:third_party/zlib.BUILD",
    sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
    strip_prefix = "zlib-1.2.11",
    urls = [
        "https://mirror.bazel.build/zlib.net/zlib-1.2.11.tar.gz",
        "https://zlib.net/zlib-1.2.11.tar.gz",
    ],
)

skylib_version = "0.9.0"
http_archive(
    name = "bazel_skylib",
    type = "tar.gz",
    url = "https://github.com/bazelbuild/bazel-skylib/releases/download/{}/bazel_skylib-{}.tar.gz".format (skylib_version, skylib_version),
    sha256 = "1dde365491125a3db70731e25658dfdd3bc5dbdfd11b840b3e987ecf043c7ca0",
)
load("@bazel_skylib//lib:versions.bzl", "versions")


new_local_repository(
    name = "macos_opencv",
    build_file = "@mediapipe//third_party:opencv_macos.BUILD",
    path = "/usr",
)

new_local_repository(
    name = "macos_ffmpeg",
    build_file = "@mediapipe//third_party:ffmpeg_macos.BUILD",
    path = "/usr",
)


http_archive(
    name = "io_bazel_rules_closure",
    sha256 = "e0a111000aeed2051f29fcc7a3f83be3ad8c6c93c186e64beb1ad313f0c7f9f9",
    strip_prefix = "rules_closure-cf1e44edb908e9616030cc83d085989b8e6cd6df",
    urls = [
        "http://mirror.tensorflow.org/github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",
        "https://github.com/bazelbuild/rules_closure/archive/cf1e44edb908e9616030cc83d085989b8e6cd6df.tar.gz",  # 2019-04-04
    ],
)


_TENSORFLOW_GIT_COMMIT = "7c09d15f9fcc14343343c247ebf5b8e0afe3e4aa"
_TENSORFLOW_SHA256= "673d00cbd2676ae43df1993e0d28c10b5ffbe96d9e2ab29f88a77b43c0211299"
http_archive(
    name = "org_tensorflow",
    urls = [
      "https://mirror.bazel.build/github.com/tensorflow/tensorflow/archive/%s.tar.gz" % _TENSORFLOW_GIT_COMMIT,
      "https://github.com/tensorflow/tensorflow/archive/%s.tar.gz" % _TENSORFLOW_GIT_COMMIT,
    ],
    patches = [
        "@mediapipe//third_party:org_tensorflow_compatibility_fixes.diff",
    ],
    patch_args = [
        "-p1",
    ],
    strip_prefix = "tensorflow-%s" % _TENSORFLOW_GIT_COMMIT,
    sha256 = _TENSORFLOW_SHA256,
)

load("@org_tensorflow//tensorflow:workspace.bzl", "tf_workspace")
tf_workspace(tf_repo_name = "org_tensorflow")
