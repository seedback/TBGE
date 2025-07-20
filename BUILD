# BUILD file for TBGE project

load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

# Example: Define a simple cc_library target
cc_library(
  name = "tbge_lib",
  srcs = glob(["src/**/*.cc"], allow_empty = True),
  hdrs = glob(["src/**/*.h", "src/**/*.hh"], allow_empty = True),
  visibility = ["//visibility:public"],
)

# Example: Define a cc_binary target
cc_binary(
  name = "tbge_main",
  srcs = ["src/main.cc"],
  deps = [":tbge_lib"],
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