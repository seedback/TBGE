# BUILD file for TBGE project
load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_binary(
    name = "tbge_main",
    srcs = ["src/main.cc"],
    deps = [
        ":tbge_lib",
        ":abseil_log",
    ],
)

cc_test(
    name = "tbge_test",
    size = "small",
    srcs = ["test/hello_test.cc"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "tbge_lib",
    srcs = glob(
        [
            "src/**/*.cc",
            "src/**/*.tcc",
        ],
        allow_empty = True,
        exclude = ["src/main.cc"],
    ),
    hdrs = glob(
        [
            "src/**/*.h",
            "src/**/*.hh",
        ],
        allow_empty = True,
    ),
    deps = [
      ":abseil_log",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
  name = "abseil_log",
  deps = [
    "@abseil-cpp//absl/log",
    "@abseil-cpp//absl/log:check",
    "@abseil-cpp//absl/log:initialize",
  ],
  visibility = ["//visibility:public"],
)