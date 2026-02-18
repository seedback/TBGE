# BUILD file for ECS library
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ecs",
    hdrs = ["ecs.h"],
    deps = [
        "//src/ecs/coordinator",
        "//src/ecs/utils",
    ],
)
