# BUILD file for ECS entity manager module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "entity_manager",
    srcs = [
        "entity_manager.cc",
    ],
    hdrs = [
        "entity_manager.h",
    ],
    deps = [
        ":entity_manager_hdrs",
        "//src/ecs/context",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_library(
    name = "entity_manager_hdrs",
    hdrs = [
        "entity_manager.h",
    ],
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/context",
    ],
)