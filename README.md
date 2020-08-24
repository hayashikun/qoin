# qoin

## Hello World
```
$ bazel build -c opt //qoin/hello_world
$ GLOG_logtostderr=1 bazel-bin/qoin/hello_world/hello_world
```

## Face mesh
```
$ bazel build -c opt //qoin/solution/face_mesh
$ GLOG_logtostderr=1 bazel-bin/qoin/solution/face_mesh \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```
--calculator_graph_config_file=graphs/face_mesh_desktop_live.pbtxt \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```

## Hand tracking
```
$ bazel build -c opt //qoin/solution/hand_tracking
$ GLOG_logtostderr=1 bazel-bin/qoin/solution/hand_tracking \
--calculator_graph_config_file=graphs/hand_tracking_desktop_live.pbtxt \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```
