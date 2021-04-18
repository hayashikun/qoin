load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "solution",
    srcs = ["solution.cc"],
    hdrs = ["solution.h"],
    deps = [
        "@com_google_absl//absl/flags:flag",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:commandlineflags",
        "@mediapipe//mediapipe/framework/port:file_helpers",
        "@mediapipe//mediapipe/framework/port:opencv_highgui",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:opencv_video",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
        "@mediapipe//mediapipe/framework/port:status",
    ],
)

cc_binary(
    name = "face_mesh",
    srcs = ["face_mesh.cc"],
    deps = [
        ":solution",
        "@mediapipe//mediapipe/graphs/face_mesh:desktop_live_calculators",
    ],
)

cc_binary(
    name = "hand_tracking",
    srcs = ["hand_tracking.cc"],
    deps = [
        ":solution",
        "@mediapipe//mediapipe/graphs/hand_tracking:desktop_tflite_calculators",
    ],
)

cc_binary(
    name = "iris_tracking",
    srcs = ["iris_tracking.cc"],
    deps = [
        ":solution",
        "@mediapipe//mediapipe/graphs/iris_tracking:iris_tracking_cpu_deps",
    ],
)