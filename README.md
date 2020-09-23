# qoin

By using `qoin`, the hand and face information detected by [mediapipe](https://github.com/google/mediapipe) can be sent to other programs by gRPC.

# Build and Run

## Hello World
```
$ bazel build -c opt //qoin/hello_world
$ GLOG_logtostderr=1 bazel-bin/qoin/hello_world/hello_world
```

## Face mesh demo
```
$ bazel build -c opt //qoin/solution:face_mesh
$ GLOG_logtostderr=1 bazel-bin/qoin/solution/face_mesh
```

## Face mesh server
```
$ bazel build -c opt //qoin/server:face_mesh
$ GLOG_logtostderr=1 bazel-bin/qoin/server/face_mesh
```

## Face mesh client
```
$ bazel build -c opt //qoin/client:face_mesh
$ GLOG_logtostderr=1 bazel-bin/qoin/client/face_mesh --url=localhost:3000
```

## Hand tracking demo
```
$ bazel build -c opt //qoin/solution:hand_tracking
$ GLOG_logtostderr=1 bazel-bin/qoin/server/hand_tracking
```

## Hand tracking server
```
$ bazel build -c opt //qoin/server:hand_tracking
$ GLOG_logtostderr=1 bazel-bin/qoin/server/hand_tracking
```

## Hand tracking server
```
$ bazel build -c opt //qoin/client:hand_tracking
$ GLOG_logtostderr=1 bazel-bin/qoin/client/hand_tracking --url=localhost:3000
```


# Demo apps

## [poin](https://github.com/hayashikun/poin)

Written in Rust

<img src="docs/poin.gif" width=600px />


## [pyoin](https://github.com/hayashikun/pyoin)

Written in Python

<img src="docs/janken.gif" width=600px />


## [qover](https://github.com/hayashikun/qover)

Written in Python


## [qoin_py](https://github.com/hayashikun/qoin_py)

Written in Python

<img src="docs/qoin_py.gif" width=600px />


