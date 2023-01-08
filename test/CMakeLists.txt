set(TARGET_NAME test)
set(TARGET_SRC_FILES src/test.cpp)

add_executable(${TARGET_NAME} ${TARGET_SRC_FILES})
#target_link_libraries(${TARGET_NAME} Qt5::Core)
target_link_libraries(${TARGET_NAME} sorts)
