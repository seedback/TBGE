# BUILD file for ECS component_array module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "component_array",
    hdrs = [
        "component_array.h",
        "component_array.tcc",
    ],
    deps = [
        "//src/ecs/context",
    ],
)
