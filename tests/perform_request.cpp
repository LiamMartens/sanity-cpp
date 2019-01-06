#include <string>
#include <fstream>
#include <thread>
#include "sanity_request.h"
#include "Catch2/single_include/catch2/catch.hpp"

using namespace std;

TEST_CASE("Create a CURL request") {
    SECTION("Should create a CURL request") {
        string line;
        string example_data = "";
        ifstream file;
        file.open("./tests/data/perform_request/example.com.html");
        while(getline(file, line)) {
            example_data += line + '\n';
        }
        file.close();
        SanityRequest req("http://example.com");

        auto when_done = [](SanityRequestResponse r) {
            return;
        };

        auto on_data = [](char* data) {
            return;
        };

        req.SetWhenDone(*when_done);
        req.SetOnData(*on_data);
        thread t = req.perform();
        t.join();
    }
}