# Add library target
add_library(${LIBRARY_NAME} STATIC random_engine.cpp)

# Specify library headers
target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link
target_link_libraries(${LIBRARY_NAME} PUBLIC ${TORCH_LIBRARIES})
