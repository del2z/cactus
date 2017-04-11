cc_library(
    name = "core",
    srcs = [
        "src/core/data_vector.cc",
        "src/core/data_matrix.cc",
    ],
    hdrs = [
        "src/core/data_vector.h",
        "src/core/data_matrix.h",
    ],
    includes = ["src"],
    deps = [
        "//external:glog",
    ],
)

cc_library(
    name = "util",
    srcs = [
        "src/util/string_alg.cc",
    ],
    hdrs = [
        "src/util/string_alg.h",
    ],
    includes = ["src"],
)

cc_library(
    name = "io",
    srcs = [
        "src/io/data_parser.cc",
    ],
    hdrs = [
        "src/io/data_parser.h",
    ],
    includes = ["src"],
    deps = [
        ":core",
        ":util",
        "//external:glog",
    ],
)

cc_library(
    name = "regularizer",
    srcs = [
        "src/regularizer/reg_base.cc",
        "src/regularizer/reg_l1.cc",
        "src/regularizer/reg_l2.cc",
    ],
    hdrs = [
        "src/regularizer/reg_base.h",
        "src/regularizer/reg_l1.h",
        "src/regularizer/reg_l2.h",
    ],
    includes = ["src"],
    deps = [
        "//external:glog",
    ],
)

cc_library(
    name = "model",
    srcs = [
        "src/optimizer/opt_base.cc",
        "src/optimizer/opt_sgd.cc",
        "src/objective/obj_base.cc",
        "src/model/model_base.cc",
        "src/model/linear.cc",
    ],
    hdrs = [
        "src/optimizer/opt_base.h",
        "src/optimizer/opt_sgd.h",
        "src/objective/obj_base.h",
        "src/objective/obj_mse.h",
        "src/model/model_base.h",
        "src/model/linear.h",
    ],
    includes = ["src"],
    deps = [
        ":core",
        ":regularizer",
        "//external:glog",
    ],
)

cc_test(
    name = "dmatrix-test",
    srcs = [
        "src/core/unit_test.cc",
    ],
    deps = [
        ":core",
        "//external:gtest",
    ],
)

cc_binary(
    name = "linear",
    srcs = [
        "src/main/linear_regressor.cc",
    ],
    includes = ["src"],
    deps = [
        ":io",
        ":regularizer",
        ":model",
        "//external:gflags",
        "//external:glog",
    ],
)
