cmake_minimum_required(VERSION 3.30)

project(XPERMath)

set(SRC_FILES __empty__.cpp Source/vector.h Source/matrix.h Source/quaternion.h)

add_executable(XPERMath ${SRC_FILES})