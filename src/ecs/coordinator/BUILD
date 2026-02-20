# BUILD file for ECS coordinator module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "coordinator",
    srcs = glob(["*.cc"], allow_empty = True),
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    deps = [
        ":coordinator_hdrs",
        "//src/ecs/component:component",
        "//src/ecs/component_manager:component_manager",
        "//src/ecs/context:context",
        "//src/ecs/entity_manager:entity_manager",
        "//src/ecs/system_manager:system_manager",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
        "@abseil-cpp//absl/log:initialize",
    ],
)

cc_library(
    name = "coordinator_hdrs",
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/component_manager:component_manager",
        "//src/ecs/context:context",
        "//src/ecs/entity_manager:entity_manager",
        "//src/ecs/system_manager:system_manager",
    ],
)