#ifndef SANITY_REQUEST_H
#define SANITY_REQUEST_H

#include <string>
#include <map>
#include <regex>
#include <thread>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <syslog.h>
#include "sanity_url.h"
#include "sanity_part_builder.h"

using json = nlohmann::json;
using namespace std;

struct InvalidMethodException
    : public exception {
    const char* what() const throw() {
        return "Invalid HTTP verb";
    }
};

struct SanityRequestResponse
{
    string Body;
    map<string, string> Headers;
};

enum class SanityRequestMethod {
    GET = 1,
    POST,
    PUT,
    PATCH,
    DELETE
};

class SanityRequest
{
private:
    const string HTTP_GET = "GET";
    const string HTTP_POST = "POST";
    const string HTTP_PUT = "PUT";
    const string HTTP_PATCH = "PATCH";
    const string HTTP_DELETE = "DELETE";

    /** the http method to call with */
    SanityRequestMethod m_method = SanityRequestMethod::GET;
    /** URL to request to */
    SanityUrl m_url;
    /** optional authorization token */
    string m_token = "";
    /** headers to send */
    map<string, string> m_headers;
    /** data to send */
    string m_data = "";
    /** response data */
    SanityRequestResponse m_response = {};

    void (*m_when_done)(SanityRequestResponse r) = nullptr;
    void (*m_on_data)(char* data) = nullptr;

    static size_t request_write_callback(char* data, size_t size, size_t data_size, void* userdata);
    static size_t request_header_callback(char* data, size_t size, size_t data_size, void* userdata);

public:
    SanityRequest(string url, string token = "");

    #pragma region getters
    string Token();
    SanityRequestMethod Method();
    string Verb();
    SanityRequestResponse Response();
    #pragma endregion

    #pragma region setters
    void SetHeader(string name, string value);
    void UnsetHeader(string name);
    void SetToken(string token);
    void SetMethod(SanityRequestMethod method);
    void SetData(string data);
    void SetData(const SanityPartBuilder& builder);
    void SetData(json data);
    void SetWhenDone(void(when_done)(SanityRequestResponse r));
    void SetOnData(void(on_data)(char* data));
    #pragma endregion

    thread perform();
};

#endif // SANITY_REQUEST_H