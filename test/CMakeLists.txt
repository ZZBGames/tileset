if (NOT GTEST_FOUND)
    message(FATAL_ERROR "Google Test is needed to build the tests.")
endif ()

set(UNIT_TEST_SOURCES
    DimensionTest.cpp
    ImageComparatorTest.cpp
    InsetsTest.cpp
    TileMapperTest.cpp
    TilesetTest.cpp)

add_executable(unittest ${UNIT_TEST_SOURCES})
target_link_libraries(unittest gtest_main pthread gtest tileset)

add_custom_target(tests unittest DEPENDS unittest COMMENT "Running unit tests...")

set(TEST_RESOURCES
    res/map.png
    res/tileset.png)
file(COPY ${TEST_RESOURCES} DESTINATION res)