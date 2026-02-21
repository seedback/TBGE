# BUILD file for Terminal library
load("@rules_cc//cc:cc_library.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "terminal",
    hdrs = glob(["*.h"]),
    deps = [
        "//src/terminal/box_drawing:box_drawing",
    ],
)
