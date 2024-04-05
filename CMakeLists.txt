# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)


project (JsonPretty
  VERSION 1.0.0
  DESCRIPTION "Pretty Print a JSON file."
  LANGUAGES CXX
)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS json)

add_executable(JsonPretty)

target_sources(JsonPretty
  PRIVATE
    src/main.cpp
)

if (MSVC)
target_compile_definitions(JsonPretty PRIVATE BOOST_JSON_NO_LIB)
endif()

target_link_libraries(JsonPretty 
  PRIVATE
    Boost::json
)

target_include_directories(JsonPretty
  PRIVATE
    ${boost_INCLUDE_DIRS}
)

include(GNUInstallDirs)

# install
install (TARGETS JsonPretty)

#testing
enable_testing()

add_test(NAME JsonPretty_print
  COMMAND JsonPretty ${PROJECT_SOURCE_DIR}/sample/sample.json)