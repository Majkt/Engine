load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "unittests",
    srcs = ["unittests.cc"],
    deps = [
        "//src/lib:CPPLib",
        "@com_google_googletest//:gtest_main",
    ],
)
