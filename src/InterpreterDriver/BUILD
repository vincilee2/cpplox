load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "interpreter-driver",
    srcs = ["InterpreterDriver.cpp"],
    hdrs = ["InterpreterDriver.h"],
    deps = [
        "//src/Types:types",
        "//src/Scanner:scanner"
    ],
)