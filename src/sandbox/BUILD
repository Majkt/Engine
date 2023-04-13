load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "assets",
    srcs = glob(["assets/**"]),
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "sandbox_app",
    srcs = ["sandbox_app.cc"],
    deps = [
        "//src/lib:engine", 
    ],
)
