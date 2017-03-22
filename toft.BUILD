cc_library(
    name = "toft",
    srcs = glob(
        ["base/**/**/*.cpp"],
        exclude = ["base/**/**/*_test.cpp"]
    ),
    hdrs = glob([
        "base/**/**/*.h",
    ]),
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

