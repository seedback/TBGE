# BUILD file for TBGE project
load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_binary(
    name = "tbge_main",
    srcs = ["src/main.cc"],
    deps = [
        ":abseil_log",
        ":tbge_lib",
        ":tbge_test_includes",
    ],
)

cc_binary(
    name = "tbge_release",
    srcs = ["src/main.cc"],
    deps = [
        ":abseil_log",
        ":tbge_lib",
    ],
)

cc_test(
    name = "tbge_test",
    size = "small",
    srcs = glob(
        [
            "test/**/*.cc",
        ],
    ),
    deps = [
        ":tbge_lib",
        ":tbge_test_includes",
    ],
)

cc_library(
    name = "tbge",
    hdrs = ["src/tbge.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/ecs:ecs",
        "//src/terminal:terminal",
    ],
)

cc_library(
    name = "tbge_lib",
    srcs = glob(
        [
            "src/**/*.cc",
        ],
        allow_empty = True,
        exclude = [
            "src/main.cc",
            "src/ecs/**/*.cc",
        ],
    ),
    hdrs = glob(
        [
            "src/**/*.h",
            "src/**/*.hh",
            "src/**/*.tcc",
        ],
        allow_empty = True,
        exclude = [
            "src/ecs/**/*.h",
            "src/ecs/**/*.tcc",
        ],
    ),
    visibility = ["//visibility:public"],
    deps = [
        ":abseil_log",
        "//src/ecs:ecs",
    ],
)

cc_library(
    name = "tbge_test_includes",
    hdrs = glob(
        [
            "test/includes/**/*.h",
            "test/includes/**/*.hh",
        ],
        allow_empty = True,
    ),
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "abseil_log",
    visibility = ["//visibility:public"],
    deps = [
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/log:initialize",
    ],
)
