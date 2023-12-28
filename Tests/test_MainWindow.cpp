#include "catch.hpp"
#include "MainWindow.h"

TEST_CASE("Testing catch2"){
    SECTION("Testing test"){
        int x = 1;
        int y = 1;

        REQUIRE(x == y);
    }
}

