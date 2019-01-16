#include "sanity_request.h"

#pragma region statics
/**
 * Callback for curl request
 * @param char* data The received data
 * @param size_t size Num of chunks, always 1
 * @param size_t data_size Size of the received data
 * @param void* userdata
 * @return size_t
 */
size_t SanityRequest::request_write_callback(char* data, size_t size, size_t data_size, void* userdata) {
    SanityRequest* req = (SanityRequest*)userdata;

    char copy[data_size + 1];
    memcpy(copy, data, data_size);
    copy[data_size] = '\0';
    req->m_response.Body += string(copy);

    if(req->m_on_data != nullptr) {
        req->m_on_data(data);
    }

    if(req->m_parse_body & req->m_on_parsed_data != nullptr) {
        json parsed = json::parse(data);
        req->m_on_parsed_data(parsed);
    }

    return data_size;
}

/**
 * Callback for curl request (headers)
 * @param char* data The received data
 * @param size_t size Num of chunks, always 1
 * @param size_t data_size Size of the received data
 * @param void* userdata
 * @return size_t
 */
size_t SanityRequest::request_header_callback(char* data, size_t size, size_t data_size, void* userdata) {
    char copy[data_size + 1];
    memcpy(copy, data, data_size);
    copy[data_size] = '\0';

    string header = copy;
    size_t index = header.find_first_of(':');
    string name = header.substr(0, index);
    string value = header.substr(index + 1, header.length() - index);
    if(index != string::npos) {
        value = regex_replace(value, regex("((^\\s+)|(\\s+$))"), "");
        name = regex_replace(name, regex("((^\\s+)|(\\s+$))"), "");
        SanityRequest* resp = (SanityRequest*)userdata;
        resp->m_response.Headers.insert(pair<string, string>(name, value));
    }

    return data_size;
}
#pragma endregion

SanityRequest::SanityRequest(string url, string token) {
    this->m_url = url;
    this->m_token = token;
}

#pragma region getters
/**
 * Gets the stored token
 * @return string
 */
string SanityRequest::Token() {
    return this->m_token;
}

/**
 * Gets the http method
 * @return SanityRequestMethod
 */
SanityRequestMethod SanityRequest::Method() {
    return this->m_method;
}

/**
 * Gets the http verb from the method
 * @return string
 */
string SanityRequest::Verb() {
    switch(this->m_method) {
        case SanityRequestMethod::POST:
            return this->HTTP_POST;
        case SanityRequestMethod::PUT:
            return this->HTTP_PUT;
        case SanityRequestMethod::PATCH:
            return this->HTTP_PATCH;
        case SanityRequestMethod::DELETE:
            return this->HTTP_DELETE;
        default:
            return this->HTTP_GET;
    }
}

/**
 * Gets the currently stored response
 * @return string
 */
SanityRequestResponse SanityRequest::Response() {
    return this->m_response;
}
#pragma endregion

#pragma region setters
/**
 * Disables parsing the response body as json
 */
void SanityRequest::DontParseBody() {
    this->m_parse_body = false;
}

/**
 * Sets a header to the request
 * @param string name The header key
 * @param string value The header value
 */
void SanityRequest::SetHeader(string name, string value) {
    this->m_headers.insert(
        pair<string, string>(
            name,
            value
        )
    );
}

/**
 * Unsets a certain header
 * @param string name The header key
 */
void SanityRequest::UnsetHeader(string name) {
    this->m_headers.erase(name);
}

/**
 * Sets the authorization token
 * @param string token The request token
 */
void SanityRequest::SetToken(string token) {
    this->m_token = token;
}

/**
 * Sets the HTTP method
 * @param string method New method
 */
void SanityRequest::SetMethod(SanityRequestMethod method) {
    if(
        method == SanityRequestMethod::GET ||
        method == SanityRequestMethod::POST ||
        method == SanityRequestMethod::DELETE ||
        method == SanityRequestMethod::PUT ||
        method == SanityRequestMethod::PATCH
    ) {
        this->m_method = SanityRequestMethod(method);
    } else {
        throw InvalidMethodException();
    }
}

/**
 * Simple data
 * @param string data
 */
void SanityRequest::SetData(string data) {
    this->m_data = data;
}

/**
 * Builder data
 * @param const SanityPartBuilder& builder
 */
void SanityRequest::SetData(const SanityPartBuilder& builder) {
    this->m_data = builder.build();
}

/**
 * Json data
 * @param json data
 */
void SanityRequest::SetData(json data) {
    this->m_data = data.dump();
}

/**
 * Sets the when done handler
 * @param void(*when_done)(SanityRequestResponse r)
 */
void SanityRequest::SetWhenDone(void(*when_done)(SanityRequestResponse r)) {
    this->m_when_done = when_done;
}

/**
 * Sets on data handler
 * @param void(*on_data)(char* data)
 */
void SanityRequest::SetOnData(void(*on_data)(char* data)) {
    this->m_on_data = on_data;
}

/**
 * Sets the on parsed data handler
 * Only relevant when DontParseBody is not used
 * This is useful when listening
 * @param void(*on_parsed_data)(json data)
 */
void SanityRequest::SetOnParsedData(void(*on_parsed_data)(json data)) {
    this->m_on_parsed_data = on_parsed_data;
}
#pragma endregion

/**
 * Performs the Sanity request
 * @return void
 */
thread SanityRequest::perform() {
    this->m_response = {
        "",
        map<string, string>()
    };

    CURL* handle;
    handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, this->m_url.build().c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &SanityRequest::request_write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
    curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, &SanityRequest::request_header_callback);
    curl_easy_setopt(handle, CURLOPT_HEADERDATA, (void*)this);

    // check http method
    if(this->m_method == SanityRequestMethod::POST) {
        curl_easy_setopt(handle, CURLOPT_POST, true);
    } else if(this->m_method != SanityRequestMethod::GET) {
        curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, this->Verb().c_str());
    }

    if(this->m_data != "") {
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, this->m_data.c_str());
    }

    // build header list
    curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    if(this->m_token != "") {
        headers = curl_slist_append(headers, string("Authorization: Bearer " + this->m_token).c_str());
    }
    map<string, string>::iterator headers_it;
    for(
        headers_it = this->m_headers.begin();
        headers_it != this->m_headers.end();
        ++headers_it
    ) {
        pair<string, string> header_pair = *headers_it;
        headers = curl_slist_append(
            headers,
            string(header_pair.first + ":" +header_pair.second).c_str()
        );
    }
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

    // perform request
    SanityRequestResponse* response = &this->m_response;
    bool parse_body = this->m_parse_body;
    void (*when_done)(SanityRequestResponse r) = this->m_when_done;
    auto curl_task = [handle, parse_body, response, when_done]() {
        CURLcode resp_code = curl_easy_perform(handle);
        if(resp_code != CURLE_OK) {
            string err = curl_easy_strerror(resp_code);
            syslog(LOG_ERR, "%s\n", err.c_str());
            throw err;
        }
        curl_easy_cleanup(handle);

        if(parse_body) {
            response->ParsedBody = json::parse(response->Body);
        }

        if(when_done != nullptr) {
            when_done(*response);
        }
    };

    thread curl_task_thread(curl_task);
    return curl_task_thread;
}
