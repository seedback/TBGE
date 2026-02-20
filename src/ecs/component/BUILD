# BUILD file for ECS component module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "component",
    hdrs = glob(["*.h"], allow_empty = True),
    deps = [
        "//src/ecs/context:context",
    ],
)