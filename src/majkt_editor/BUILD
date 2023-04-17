load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "assets",
    srcs = glob(["assets/**"]),
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "majkt_editor",
    srcs = glob(["*.cc", "*.h"]),
    deps = [
        "//src/lib:engine", 
    ],
)
