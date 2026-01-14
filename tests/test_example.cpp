#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <iostream>
#include <memory>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST_CASE( "Simple Test" )
{
    int i = 42;
    
    REQUIRE( i == 42 );
}

