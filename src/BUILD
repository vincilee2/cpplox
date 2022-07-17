load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

cc_binary(
    name = "cpplox",
    srcs = ["main.cpp"],
    deps = [
        ":token_type_lib",
        ":interpreter-driver",
    ],
)

cc_library(
    name = "token_type_lib",
    srcs = ["TokenType.cpp"],
    hdrs = ["TokenType.h"],
)

cc_library(
    name = "interpreter-driver",
    srcs = ["InterpreterDriver.cpp"],
    hdrs = ["InterpreterDriver.h"],
    deps = [":token_type_lib"],
)