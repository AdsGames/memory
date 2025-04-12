cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# ---- Project ----

project (
  Memory
  VERSION 0.1.0
  LANGUAGES CXX
)

# ---- Dependencies ----

include(cmake/get_cpm.cmake)
CPMAddPackage("gh:adsgames/asw@0.5.7")

# ---- Source code ----

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# ---- Executable ----

add_executable (${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# ---- Libs ----

if(MINGW)
  target_link_libraries(${PROJECT_NAME} -lmingw32)
endif(MINGW)

target_link_libraries(
  ${PROJECT_NAME} 
  asw
)

# ---- Emscripten ----

if(EMSCRIPTEN)
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")

  target_link_libraries(
    ${PROJECT_NAME} 
    -sWASM=1 
    -sALLOW_MEMORY_GROWTH=1 
    -sMAXIMUM_MEMORY=1gb
  )

  set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES 
    LINK_FLAGS
    "--preload-file ${CMAKE_CURRENT_LIST_DIR}/assets@/assets --use-preload-plugins --shell-file ${CMAKE_CURRENT_LIST_DIR}/index.html"
  )
endif(EMSCRIPTEN)

# ---- Assets ----

file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

