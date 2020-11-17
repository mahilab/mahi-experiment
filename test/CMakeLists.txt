# create test executable and link it to mahi-util
add_executable(test_command_line_args test_command_line_args.cpp)
target_link_libraries(test_command_line_args mahi::util)

# create test executable and link it to mahi-util
add_executable(test_loading_data test_loading_data.cpp)
target_link_libraries(test_loading_data mahi::util)

# create test executable and link it to mahi-util
add_executable(test_console_input test_console_input.cpp)
target_link_libraries(test_console_input mahi::util)

# create test executable and link it to mahi-util
add_executable(test_randomization test_randomization.cpp)
target_link_libraries(test_randomization mahi::util)

# create test executable and link it to mahi-util
add_executable(test_collecting_data test_collecting_data.cpp)
target_link_libraries(test_collecting_data mahi::util)

# create test executable and link it to mahi-util
add_executable(test_timing_elements test_timing_elements.cpp)
target_link_libraries(test_timing_elements mahi::util)

# create test executable and link it to mahi-util
add_executable(test_saving_data test_saving_data.cpp)
target_link_libraries(test_saving_data mahi::util)