git_repository(
    name = "com_github_gflags_gflags",
    commit = "f8a0efe03aa69b3336d8e228b37d4ccb17324b88",
    remote = "https://github.com/gflags/gflags.git",
)

bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

new_http_archive(
    name = "com_github_google_gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.0.zip",
    sha256 = "f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf",
    build_file = "gtest.BUILD",
    strip_prefix = "googletest-release-1.8.0/googletest",
)

bind(
    name = "gtest",
    actual = "@com_github_google_gtest//:gtest",
)

new_http_archive(
    name = "com_github_chen3feng_toft",
    url = "https://github.com/chen3feng/toft/archive/master.zip",
    sha256 = "a1330a619e3e98dd539508d5521f794dc6a83fc9fb454cd7de7cbfd5b70b9bf1",
    build_file = "toft.BUILD",
    strip_prefix = "toft-master",
)

bind(
    name = "toft",
    actual = "@com_github_chen3feng_toft//:toft",
)
