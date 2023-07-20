project(strassenLib)

add_library(${PROJECT_NAME} 
${PROJECT_SOURCE_DIR}/src/matrix.cc
${PROJECT_SOURCE_DIR}/src/strassen.cc
)
add_library(lib::strassenLib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
