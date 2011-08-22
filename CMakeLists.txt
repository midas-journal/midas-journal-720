cmake_minimum_required(VERSION 2.6)

PROJECT(SuperPixelSegmentation)
ENABLE_TESTING()

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(SuperPixelSegmentation Example.cxx vtkSuperPixelSegmentation.cxx
disjoint-set.cxx
imconv.cxx
filter.cxx
segment-graph.cxx
segment-image.cxx
)
TARGET_LINK_LIBRARIES(SuperPixelSegmentation vtkHybrid)


ADD_EXECUTABLE(Test Test.cxx vtkSuperPixelSegmentation.cxx
disjoint-set.cxx
imconv.cxx
filter.cxx
segment-graph.cxx
segment-image.cxx
)
TARGET_LINK_LIBRARIES(Test vtkHybrid)
ADD_TEST(Test Test beach.jpg output.jpg)

