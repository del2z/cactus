cc_library(
    name = "core-lib",
    srcs = [
        "src/core/data_vector.cc",
        "src/core/data_matrix.cc",
        "src/core/objective.cc",
        "src/core/regularizer.cc",
        "src/core/optimizer.cc",
    ],
    hdrs = [
        "src/core/data_vector.h",
        "src/core/data_matrix.h",
        "src/core/objective.h",
        "src/core/regularizer.h",
        "src/core/optimizer.h",
    ],
    includes = ["src"],
    deps = [
        "//external:glog",
    ],
)

cc_library(
    name = "util-lib",
    srcs = [
        "src/utils/string_alg.cc",
    ],
    hdrs = [
        "src/utils/string_alg.h",
    ],
    includes = ["src"],
)

cc_library(
    name = "io-lib",
    srcs = [
        "src/io/data_parser.cc",
    ],
    hdrs = [
        "src/io/data_parser.h",
    ],
    deps = [
        ":core-lib",
        ":util-lib",
        "//external:glog",
    ],
)

cc_library(
    name = "linear-lib",
    srcs = [
        "src/core/linear_model.cc",
    ],
    hdrs = [
        "src/core/linear_model.h",
    ],
    includes = ["src"],
    deps = [
        ":io-lib",
    ],
)

cc_test(
    name = "dmatrix-test",
    srcs = ["src/core/unit_test.cc"],
    deps = [
        "//external:gtest",
        ":core-lib",
    ],
)

cc_binary(
    name = "linear",
    srcs = [
        "src/main/linear_regressor.cc"
    ],
    deps = [
        ":io-lib",
        ":linear-lib",
        "//external:gflags",
        "//external:glog",
    ],
)
