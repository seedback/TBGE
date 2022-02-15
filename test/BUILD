cc_library(
    name = "test",
    srcs = glob(["**/*.cc"]),
    hdrs = glob(["**/*.hh"]),
    deps = [
      "//src/lib:lib",
      "@shf//:shf",
      "@gtest//:gtest",
    ],
    visibility = ["//visibility:public"],
)


cc_binary(
  name = "test_main",
	srcs = ["main_test.cc"],
	deps = [
    "//test:test",
    "//src/lib:lib",
    "//include:include",
    "@shf//:shf",
    "@gtest//:gtest",
  ],
	visibility = ["//visibility:public"],
)