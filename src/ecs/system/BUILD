# BUILD file for ECS system module
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "system",
    hdrs = glob(["*.h"], allow_empty = True),
    deps = [
        "//src/ecs/context:context",
    ],
)