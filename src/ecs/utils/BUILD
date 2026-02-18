# BUILD file for ECS utils module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "setup_console",
    hdrs = ["setup_console.h"],
    deps = [
        "//src/ecs/context",
    ],
)

cc_library(
    name = "utils",
    deps = [
        ":setup_console",
    ],
)
