#ifndef SANITY_REQUEST_H
#define SANITY_REQUEST_H

#include <cstdio>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <thread>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <syslog.h>
#include <sys/stat.h>
#include "sanity_url.h"
#include "sanity_part_builder.h"

using json = nlohmann::json;
using namespace std;

#pragma region exceptions
struct SanityRequest_InvalidMethodException
    : public exception {
    const char* what() const throw() {
        return "Invalid HTTP verb";
    }
};

struct SanityRequest_InvalidUploadFileException
    : public exception {
    const char* what() const throw() {
        return "Could not find file for upload";
    }
};
#pragma endregion

struct SanityRequestResponse
{
    string Body;
    json ParsedBody;
    map<string, string> Headers;
    void* Userdata;
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

    /** @var the http method to call with */
    SanityRequestMethod m_method = SanityRequestMethod::GET;
    /** @var URL to request to */
    SanityUrl m_url;
    /** @var The mime type to use with the request */
    string m_mime_type = "application/json";
    /** @var optional authorization token */
    string m_token = "";
    /** @var headers to send */
    map<string, string> m_headers;
    /** @var data to send */
    string m_data = "";
    /** @var file path to upload */
    string m_upload_file = "";
    /** @var whether to parse the body as JSON */
    bool m_parse_body = true;
    /** @var whether to store the response in memory, if set to false it will be saved in a tmp file. (can not be used with parse body) */
    bool m_store_in_mem = true;
    /** @var Whether to keep the tmp file after request */
    bool m_keep_tmp_file = false;
    /** @var response data */
    SanityRequestResponse m_response = {};

    void (*m_when_done)(SanityRequestResponse r) = nullptr;
    void (*m_on_data)(char* data) = nullptr;
    void (*m_on_parsed_data)(json data) = nullptr;

    static size_t request_write_callback(char* data, size_t size, size_t data_size, void* userdata);
    static size_t request_header_callback(char* data, size_t size, size_t data_size, void* userdata);

public:
    SanityRequest(string url, string token = "");

    #pragma region getters
    string MimeType() const;
    string Token() const;
    SanityRequestMethod Method() const;
    string Verb() const;
    SanityRequestResponse Response() const;
    #pragma endregion

    #pragma region setters
    void DontParseBody();
    void DontStoreInMem();
    void KeepTmpFile();
    void SetMimeType(string mime);
    void SetHeader(string name, string value);
    void UnsetHeader(string name);
    void SetToken(string token);
    void SetMethod(SanityRequestMethod method);
    void SetData(string data);
    void SetData(const SanityPartBuilder& builder);
    void SetData(json data);
    void SetUploadFile(string file, string mime_type);
    void SetWhenDone(void(when_done)(SanityRequestResponse r));
    void SetOnData(void(on_data)(char* data));
    void SetOnParsedData(void(on_parsed_data)(json data));
    #pragma endregion

    thread perform(void* userdata = nullptr);
};

#endif // SANITY_REQUEST_H