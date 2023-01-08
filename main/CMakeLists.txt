#find_package(Qt5 COMPONENTS Core REQUIRED)

set(TARGET_NAME main)
set(TARGET_SRC_FILES src/main.cpp)

add_executable(${TARGET_NAME} ${TARGET_SRC_FILES})
#target_link_libraries(${TARGET_NAME} Qt5::Core)
target_link_libraries(${TARGET_NAME} ui)
