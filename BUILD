load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "x",
    srcs = [
        "dl.cpp",
        "error.cpp",
        "fs.cpp",
        "include/x/dl.hpp",
        "include/x/error.hpp",
        "include/x/fs.hpp",
        "include/x/mmap.hpp",
        "include/x/timer.hpp",
        "mmap.cpp",
    ],
    hdrs = ["include/x.hpp"],
    copts = ["-Iinclude"],
)
