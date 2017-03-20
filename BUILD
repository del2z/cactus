cc_library(
    name = "core_dmatrix",
    srcs = [
        "src/core/data_vector.cc",
        "src/core/data_matrix.cc",
    ],
    hdrs = [
        "src/core/data_vector.h",
        "src/core/data_matrix.h",
    ],
    includes = ["src"]
)

cc_test(
    name = "dmatrix-test",
    srcs = ["src/core/unit_test.cc"],
    deps = [
        "//external:gtest",
        ":core_dmatrix",
    ],
)

cc_binary(
    name = "linear",
    srcs = [
        "src/main/linear_regressor.cc"
    ],
    deps = [
        "//external:gflags",
    ],
)
