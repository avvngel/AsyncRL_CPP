# Executables
add_executable(test_TrainingStep test_TrainingStep.cpp)

# Header files
target_include_directories(test_TrainingStep PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Test Declarations
add_test(NAME TestTrainingStep COMMAND test_TrainingStep)

