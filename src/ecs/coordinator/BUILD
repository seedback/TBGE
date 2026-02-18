# BUILD file for ECS coordinator module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "coordinator",
    srcs = [
        "coordinator.cc",
    ],
    hdrs = [
        "coordinator.h",
        "coordinator.tcc",
    ],
    deps = [
        ":coordinator_hdrs",
        "//src/ecs/component",
        "//src/ecs/component_manager",
        "//src/ecs/context",
        "//src/ecs/entity_manager",
        "//src/ecs/system_manager",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/log:initialize",
    ],
)

cc_library(
    name = "coordinator_hdrs",
    hdrs = [
        "coordinator.h",
        "coordinator.tcc",
    ],
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/component_manager",
        "//src/ecs/context",
        "//src/ecs/entity_manager",
        "//src/ecs/system_manager",
    ],
)