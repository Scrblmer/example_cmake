#include <catch2/catch_all.hpp>

TEST_CASE("Hello, World!", "[hello]") {
    REQUIRE(1 == 1);
}

int* get_int() {
    return new int;
}

TEST_CASE("Test leak", "[memcheck]") {
    int* a = get_int();
    *a = 1;
    REQUIRE(*a == 1);
}