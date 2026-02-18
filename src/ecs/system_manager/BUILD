# BUILD file for ECS system manager module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "system_manager",
    srcs = [
        "system_manager.cc",
    ],
    hdrs = [
        "system_manager.h",
        "system_manager.tcc",
    ],
    deps = [
        ":system_manager_hdrs",
        "//src/ecs/context",
        "//src/ecs/system",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_library(
    name = "system_manager_hdrs",
    hdrs = [
        "system_manager.h",
        "system_manager.tcc",
    ],
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/context",
        "//src/ecs/system",
    ],
)