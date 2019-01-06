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
    SanityRequest* resp = (SanityRequest*)userdata;
    resp->m_response.Body += data;
    if(resp->m_on_data != nullptr) {
        resp->m_on_data(data);
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
    string header = data;
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
 * @return string
 */
string SanityRequest::Method() {
    return this->m_method;
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
 * Sets a header to the request
 * @param string name The header key
 * @param string value The header value
 * @return SanityRequest*
 */
SanityRequest* SanityRequest::SetHeader(string name, string value) {
    this->m_headers.insert(
        pair<string, string>(
            name,
            value
        )
    );
    return this;
}

/**
 * Unsets a certain header
 * @param string name The header key
 * @return SanityRequest*
 */
SanityRequest* SanityRequest::UnsetHeader(string name) {
    this->m_headers.erase(name);
    return this;
}

/**
 * Sets the authorization token
 * @param string token The request token
 * @return SanityRequest*
 */
SanityRequest* SanityRequest::SetToken(string token) {
    this->m_token = token;
    return this;
}

/**
 * Sets the HTTP method
 * @param string method New method
 * @return SanityRequest*
 */
SanityRequest* SanityRequest::SetMethod(string method) {
    if(
        method == SanityRequest::HTTP_METHOD_GET ||
        method == SanityRequest::HTTP_METHOD_POST ||
        method == SanityRequest::HTTP_METHOD_DELETE ||
        method == SanityRequest::HTTP_METHOD_PUT
    ) {
        this->m_method = method;
    } else {
        throw InvalidMethodException();
    }

    return this;
}

/**
 * Sets the when done handler
 * @param void(*when_done)(SanityRequestResponse r)
 * @return SanityReauest*
 */
SanityRequest* SanityRequest::SetWhenDone(void(*when_done)(SanityRequestResponse r)) {
    this->m_when_done = when_done;
    return this;
}

SanityRequest* SanityRequest::SetOnData(void(*on_data)(char* data)) {
    this->m_on_data = on_data;
    return this;
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
    curl_easy_setopt(handle, CURLOPT_URL, this->m_url.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &SanityRequest::request_write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)this);
    curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, &SanityRequest::request_header_callback);
    curl_easy_setopt(handle, CURLOPT_HEADERDATA, (void*)this);

    // check http method
    if(this->m_method == SanityRequest::HTTP_METHOD_POST) {
        curl_easy_setopt(handle, CURLOPT_POST, true);
    } else if(this->m_method != SanityRequest::HTTP_METHOD_GET) {
        curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, this->m_method.c_str());
    }

    if(this->m_data != "") {
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, this->m_data);
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
    void (*when_done)(SanityRequestResponse r) = this->m_when_done;
    auto curl_task = [handle, response, when_done]() {
        CURLcode resp_code = curl_easy_perform(handle);
        if(resp_code != CURLE_OK) {
            throw curl_easy_strerror(resp_code);
        }
        curl_easy_cleanup(handle);

        if(when_done != nullptr) {
            when_done(*response);
        }
    };

    thread curl_task_thread(curl_task);
    return curl_task_thread;
}

