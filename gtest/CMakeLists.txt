add_executable(test_main test_main.cpp ../rb_tree.hpp)
target_link_libraries(test_main ${GTEST_LIBRARY} pthread)
install(TARGETS test_main RUNTIME DESTINATION bin)
