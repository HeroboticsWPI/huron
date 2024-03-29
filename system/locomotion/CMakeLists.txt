set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND SOURCE_FILES
  "${dir}/src/zero_moment_point.cc"
  "${dir}/src/zero_moment_point_fsr_array.cc"
  "${dir}/src/zero_moment_point_ft_sensor.cc"
  "${dir}/src/zero_moment_point_total.cc")
FILE(GLOB_RECURSE HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

list(APPEND TEST_SOURCE_FILES
        "${dir}/test/test_zero_moment_point.cc")

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_sources(huron
    PRIVATE
    ${SOURCE_FILES}
    # PUBLIC
    # ${HEADER_FILES}
)
target_include_directories(huron
    PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include> 
)

target_sources(huron_tests
  PRIVATE
  ${TEST_SOURCE_FILES}
)
target_include_directories(huron_tests
        PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${INCLUDE_DIRS} DESTINATION include)
