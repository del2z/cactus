git_repository(
    name = "com_github_gflags",
    commit = "f8a0efe03aa69b3336d8e228b37d4ccb17324b88",
    remote = "https://github.com/gflags/gflags.git",
)

bind(
    name = "gflags",
    actual = "@com_github_gflags//:gflags",
)

new_http_archive(
    name = "com_github_gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.0.zip",
    sha256 = "f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf",
    build_file = "gtest.BUILD",
    strip_prefix = "googletest-release-1.8.0/googletest",
)

bind(
    name = "gtest",
    actual = "@com_github_gtest//:gtest",
)
