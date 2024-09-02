# Executables
add_executable(test_random_engine test_random_engine.cpp)
add_executable(test_actor test_actor.cpp)


# Header files
target_include_directories(test_random_engine PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_actor PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Depenencies
target_link_libraries(test_random_engine PRIVATE ${LIBRARY_NAME})
target_link_libraries(test_actor PRIVATE ${LIBRARY_NAME})

# Test Declarations
add_test(NAME TestRandomEngine COMMAND test_random_engine)
add_test(NAME TestActor COMMAND test_actor)

