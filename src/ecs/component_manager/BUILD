# BUILD file for ECS component manager module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "component_manager",
    srcs = glob(["*.cc"], allow_empty = True),
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    deps = [
        ":component_manager_hdrs",
        "//src/ecs/component_array:component_array",
        "//src/ecs/context:context",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_library(
    name = "component_manager_hdrs",
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/component_array:component_array",
        "//src/ecs/context:context",
    ],
)