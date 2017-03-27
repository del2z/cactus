local_repository(
    name = "com_github_gflags_gflags",
    path = "third_party/gflags-2.2.0",
)

bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

new_local_repository(
    name = "com_github_google_gtest",
    path = "third_party/googletest-1.8.0/googletest",
    build_file = "gtest.BUILD",
)

bind(
    name = "gtest",
    actual = "@com_github_google_gtest//:gtest",
)

new_local_repository(
    name = "com_github_google_glog",
    path = "third_party/glog-0.3.4",
    build_file = "glog.BUILD",
)

bind(
    name = "glog",
    actual = "@com_github_google_glog//:glog",
)
