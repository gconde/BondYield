
load("qt.bzl", "qt_cc_library", "qt_ui_library")

qt_cc_library(
    name = "ByLib",
    srcs = ["BondMath.cpp", "BondYieldForm.cpp"],
    hdrs = ["BondMath.h", "BondYieldForm.h", "DoubleValidator.hpp"],
    deps = ["@qt//:qt_widgets"],
)

cc_binary(
    name = "BondYield",
    srcs = ["main.cpp"],
    deps = [
        "@qt//:qt_widgets",
        ":ByLib"
    ],
)