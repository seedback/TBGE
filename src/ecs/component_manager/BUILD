# BUILD file for ECS component manager module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "component_manager",
    srcs = [
        "component_manager.cc",
    ],
    hdrs = [
        "component_manager.h",
        "component_manager.tcc",
    ],
    deps = [
        ":component_manager_hdrs",
        "//src/ecs/component_array",
        "//src/ecs/context",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_library(
    name = "component_manager_hdrs",
    hdrs = [
        "component_manager.h",
        "component_manager.tcc",
    ],
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/component_array",
        "//src/ecs/context",
    ],
)