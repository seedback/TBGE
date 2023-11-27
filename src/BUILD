cc_library(
  name = "tbge_lib",
  srcs = glob(["**/*.c", "**/*.cc"]),
  hdrs = glob(["**/*.h", "**/*.hh"]),
  # copts = ["-Isrc"],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "tbge",
  srcs = ["main.cc"],
  deps = [":tbge_lib"],
)
