# BUILD file for ECS system manager module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "system_manager",
    srcs = glob(["*.cc"], allow_empty = True),
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    deps = [
        ":system_manager_hdrs",
        "//src/ecs/context:context",
        "//src/ecs/system:system",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_library(
    name = "system_manager_hdrs",
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/context:context",
        "//src/ecs/system:system",
    ],
)