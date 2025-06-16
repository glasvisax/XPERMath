cmake_minimum_required(VERSION 3.30)

project(XPERMath)

file(GLOB_RECURSE src xm/*.h)

set(SRC_FILES __empty__.cpp ${src})

add_executable(XPERMath ${SRC_FILES})