# BUILD file for ECS entity manager module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "entity_manager",
    srcs = glob(["*.cc"], allow_empty = True),
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    deps = [
        ":entity_manager_hdrs",
        "//src/ecs/context:context",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/log:check",
    ],
)

cc_library(
    name = "entity_manager_hdrs",
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    visibility = ["//visibility:private"],
    deps = [
        "//src/ecs/context:context",
    ],
)