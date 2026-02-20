# BUILD file for ECS component_array module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "component_array",
    hdrs = glob(["*.h", "*.tcc"], allow_empty = True),
    deps = [
        "//src/ecs/context:context",
    ],
)
