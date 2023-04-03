cc_test(
  name = "hello_test",
  size = "small",
  srcs = ["tests/hello_test.cc"],
  deps = ["@com_google_googletest//:gtest_main"],
)

cc_test(
  name = "test_all",
  size = "small",
  srcs = ["tests/game_object/game_object_test.cc"],
  deps = [
    "@com_google_googletest//:gtest_main",
    "//src:src"
    ],
)