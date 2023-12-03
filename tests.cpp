#include <catch2/catch_all.hpp>

TEST_CASE("Hello, World!", "[hello]") {
    REQUIRE(1 == 1);
}

TEST_CASE("Test leak", "[memcheck]") {
    int* a = new int;
    REQUIRE(1 == 1);
}