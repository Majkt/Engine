load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "events",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "//src/lib/core:core_for_editor",
    ],
)

load("//tools:cpplint.bzl", "cpplint")

exports_files([
    "CPPLINT.cfg",
])

cpplint()
