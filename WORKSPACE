local_repository(
    name = "com_github_gflags_gflags",
    path = "third_party/gflags",
)

bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

new_local_repository(
    name = "com_github_google_gtest",
    path = "third_party/googletest/googletest",
    build_file = "third_party/gtest.BUILD",
)

bind(
    name = "gtest",
    actual = "@com_github_google_gtest//:gtest",
)

new_local_repository(
    name = "com_github_google_glog",
    path = "third_party/glog",
    build_file = "third_party/glog.BUILD",
)

bind(
    name = "glog",
    actual = "@com_github_google_glog//:glog",
)

