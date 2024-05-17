cmake_minimum_required(VERSION 3.10)
project(test_task)
set(SRC_LIST src/main.cpp src/event/event.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

enable_testing()


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SRC_LIST tests/test.cpp src/event/event.cpp)
add_executable(run_test ${TEST_SRC_LIST})

target_link_libraries(run_test ${GTEST_BOTH_LIBRARIES})

add_test(Test1 run_test tests/input/test1.txt tests/output/test1.txt)
add_test(Test2 run_test tests/input/test2.txt tests/output/test2.txt)
add_test(Test3 run_test tests/input/test3.txt tests/output/test3.txt)
add_test(Test4 run_test tests/input/test4.txt tests/output/test4.txt)
add_test(Test5 run_test tests/input/test5.txt tests/output/test5.txt)
add_test(Test6 run_test tests/input/test6.txt tests/output/test6.txt)
add_test(Test7 run_test tests/input/test7.txt tests/output/test7.txt)
add_test(Test8 run_test tests/input/test8.txt tests/output/test8.txt)
add_test(Test9 run_test tests/input/test9.txt tests/output/test9.txt)
add_test(Test10 run_test tests/input/test10.txt tests/output/test10.txt)