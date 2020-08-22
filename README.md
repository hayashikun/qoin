# qoin

## Hello World
```
$ bazel build -c opt //qoin/hello_world
$ GLOG_logtostderr=1 bazel-bin/qoin/hello_world/hello_world
```

## Face mesh
```
$ bazel build -c opt //qoin/face_mesh
$ GLOG_logtostderr=1 bazel-bin/qoin/face_mesh/face_mesh \
--calculator_graph_config_file=graphs/face_mesh_desktop_live.pbtxt \
--mediapipe_resource_root=bazel-qoin/external/mediapipe
```