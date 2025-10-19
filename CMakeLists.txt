cmake_minimum_required(VERSION 3.24)

project("Farming Simulator")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(farm_printer_test tests/farm_printer_test.cpp src/farm_printer.cpp src/farm.cpp src/soil.cpp src/player.cpp)
add_executable(farm_test tests/farm_test.cpp src/farm.cpp src/soil.cpp src/carrot.cpp src/player.cpp)
add_executable(soil_test tests/soil_test.cpp src/soil.cpp)
add_executable(carrot_test tests/carrot_test.cpp src/carrot.cpp)
add_executable(player_test tests/player_test.cpp src/player.cpp)
add_executable(main main.cpp src/farm.cpp src/farm_printer.cpp src/soil.cpp src/carrot.cpp src/player.cpp)

target_link_libraries(farm_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(farm_printer_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(soil_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(carrot_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(player_test PRIVATE Catch2::Catch2WithMain)