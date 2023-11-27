# Add the following to your BUILD file to link against gtest and gmock
cc_library(
    name = "test_lib",
    hdrs = glob(["**/*.h", "**/*.hh"]),
    copts = ["-Itests"],
)

cc_test(
    name = "test_all",
    srcs = glob(["tests/**/*.c", "tests/**/*.cc"]),
    deps = [
        "//:test_lib",
        "//src:tbge_lib",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "game_objects_test",
    srcs = glob(["**/*.c", "**/*.cc"]),
    deps = [
        "//:test_lib",
        "//src:tbge_lib",
        "@gtest//:gtest_main",
    ],
)