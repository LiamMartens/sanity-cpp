#ifndef SANITY_REQUEST_H
#define SANITY_REQUEST_H

#include <string>
#include <map>
#include <regex>
#include <thread>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

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

class SanityRequest
{

    const string HTTP_METHOD_GET = "GET";
    const string HTTP_METHOD_POST = "POST";
    const string HTTP_METHOD_DELETE = "DELETE";
    const string HTTP_METHOD_PUT = "PUT";

private:
    /** the http method to call with */
    string m_method = SanityRequest::HTTP_METHOD_GET;
    /** URL to request to */
    string m_url = "";
    /** optional authorization token */
    string m_token = "";
    /** headers to send */
    map<string, string> m_headers;
    /** data to send */
    string m_data = "";
    /** response data */
    SanityRequestResponse m_response = {};

    /** */
    void (*m_when_done)(SanityRequestResponse r) = nullptr;
    void (*m_on_data)(char* data) = nullptr;

    static size_t request_write_callback(char* data, size_t size, size_t data_size, void* userdata);
    static size_t request_header_callback(char* data, size_t size, size_t data_size, void* userdata);

public:
    SanityRequest(string url, string token = "");

    string Token();
    string Method();
    SanityRequestResponse Response();

    SanityRequest* SetHeader(string name, string value);
    SanityRequest* UnsetHeader(string name);
    SanityRequest* SetToken(string token);
    SanityRequest* SetMethod(string method);
    SanityRequest* SetWhenDone(void(when_done)(SanityRequestResponse r));
    SanityRequest* SetOnData(void(on_data)(char* data));

    thread perform();
};

#endif // SANITY_REQUEST_H