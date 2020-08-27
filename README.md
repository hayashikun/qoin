# qoin

By using `qoin`, the hand and face information detected by [mediapipe](https://github.com/google/mediapipe) can be sent to other programs by gRPC.

# Build and Run

I have only tested it on macOS, and it probably won't build properly on other environments.

## Hello World
```
$ bazel build -c opt //qoin/hello_world
$ GLOG_logtostderr=1 bazel-bin/qoin/hello_world/hello_world
```

## Face mesh
```
$ bazel build -c opt //qoin/solution:face_mesh
$ GLOG_logtostderr=1 bazel-bin/qoin/solution/face_mesh \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```

## Face mesh server
```
$ bazel build -c opt //qoin/server:face_mesh_server
$ GLOG_logtostderr=1 bazel-bin/qoin/server/face_mesh_server \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```

## Hand tracking
```
$ bazel build -c opt //qoin/solution:hand_tracking
$ GLOG_logtostderr=1 bazel-bin/qoin/server/hand_tracking \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```

## Hand tracking server
```
$ bazel build -c opt //qoin/server:hand_tracking
$ GLOG_logtostderr=1 bazel-bin/qoin/server/hand_tracking \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```

# Apps

## [qoin_py](https://github.com/hayashikun/qoin_py)

Written in Python

<img src="docs/qoin_py.gif" width=600px />

## [poin](https://github.com/hayashikun/poin)

Written in Rust

<img src="docs/poin.gif" width=600px />

