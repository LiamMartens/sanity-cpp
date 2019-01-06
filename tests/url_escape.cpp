#include <stdio.h>
#include <string>
#include <cstring>
#include <curl/curl.h>
#include "Catch2/single_include/catch2/catch.hpp"

using namespace std;

TEST_CASE("T") {
    char input[] = "hello world";
    char output[] = "hello%20world";
    char* result = curl_easy_escape(nullptr, input, strlen(input));
    REQUIRE(string(output) == string(result));
}