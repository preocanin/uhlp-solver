set(SOURCES
    parameter/parameter_reader.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    ${CONAN_LIBS}
    ${PROJECT_NAME}_lib)
