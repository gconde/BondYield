#!/bin/sh

qmake-qt5 -o Makefile BondYield.pro
make compiler_moc_predefs_make_all mocables all
