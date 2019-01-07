#include "sanity_url.h"
#include <iostream>

#pragma region scheme constants
const string SanityUrl::SCHEME_HTTP = "http";
const string SanityUrl::SCHEME_HTTPS = "https";
const string SanityUrl::SCHEME_FTP = "ftp";
const string SanityUrl::SCHEME_FTPS = "ftps";
const string SanityUrl::SCHEME_FILE = "file";
#pragma endregion

#pragma region regexes
const regex SanityUrl::RX_HOSTNAME = regex("(([a-zA-Z0-9]+\\.)+([a-zA-Z0-9]+))", regex::extended);
#pragma endregion

#pragma region constructors
SanityUrl::SanityUrl() {
    this->m_type = SanityPartBuilderType::SURL;
}

SanityUrl::SanityUrl(string parse)
    : SanityUrl() {
    string leftover = parse;

    // extract scheme
    size_t scheme_idx = leftover.find(':');
    if(scheme_idx == string::npos) {
        throw NoSchemeException();
    }
    string scheme = leftover.substr(0, scheme_idx);
    this->SetScheme(scheme);
    leftover = leftover.substr(scheme_idx + 3);

    // extract hostname
    smatch hostname_match;
    regex_search(leftover, hostname_match, SanityUrl::RX_HOSTNAME);
    if(hostname_match.size() < 2) {
        throw InvalidHostnameException();
    } else {
        string hostname = string(hostname_match[0]);
        this->SetHostname(hostname);
        leftover = leftover.substr(hostname.size());
    }

    // extract path
    size_t next_path_idx = leftover.find('/');
    while(next_path_idx != string::npos) {
        string part = leftover.substr(0, next_path_idx);
        leftover = leftover.substr(next_path_idx + 1);
        next_path_idx = leftover.find('/');
        if(!part.empty()) {
            this->PushPath(part);
        }
    }
    next_path_idx = leftover.find_first_of("?#");
    string last_part = next_path_idx == string::npos ? leftover : leftover.substr(0, next_path_idx);
    if(!last_part.empty()) {
        this->PushPath(last_part);
        leftover = leftover.substr(last_part.size());
    }

    // extract fragment
    size_t fragment_start_idx = leftover.find('#');
    if(fragment_start_idx != string::npos) {
        this->SetFragment(leftover.substr(fragment_start_idx + 1));
        leftover = leftover.substr(0, fragment_start_idx);
    }

    // extract query
    if(!leftover.empty()) {
        size_t query_start_idx = leftover.find('?');
        if(query_start_idx != string::npos) {
            leftover = leftover.substr(1);
            vector<string> params = SanityString::Split(leftover, '&');
            for(auto p : params) {
                vector<string> keyval = SanityString::Split(p, '=');
                if(keyval.size() == 2) {
                    string value = keyval[1];
                    int outlength;
                    value = curl_easy_unescape(nullptr, value.c_str(), value.size(), &outlength);
                    this->InsertQueryPart(keyval[0], value);
                } else {
                    this->InsertQueryPart(keyval[0], "");
                }
            }
        }
    }
}

SanityUrl::SanityUrl(const SanityUrl& url) {
    this->m_scheme = url.m_scheme;
    this->m_hostname = url.m_hostname;
    this->m_port = url.m_port;
    this->m_fragment = url.m_fragment;
    for(auto part : url.m_path) {
        this->PushPath(part);
    }
    for(auto part : url.m_query) {
        this->InsertQueryPart(part.first, part.second);
    }
}
#pragma endregion

#pragma region getters
/**
 * Gets the string equivalent of the HTTP scheme
 * @return string const
 */
string SanityUrl::Scheme() const {
    return this->m_scheme;
}

/**
 * Gets the hostname
 * @return string const
 */
string SanityUrl::Hostname() const {
    return this->m_hostname;
}

/**
 * Gets the port
 * @return unsigned int
 */
unsigned int SanityUrl::Port() const {
    return this->m_port;
}

/**
 * Gets the path
 * @return vector<string>
 */
vector<string> SanityUrl::Path() const {
    vector<string> path_copy;
    for(auto part : this->m_path) {
        path_copy.push_back(part);
    }
    return path_copy;
}

/**
 * Gets the query copy
 * @return map<string, string>
 */
map<string, string> SanityUrl::Query() const {
    map<string, string> query_copy;
    for(auto part : this->m_query) {
        query_copy.insert(pair<string, string>(
            part.first,
            part.second
        ));
    }
}

/**
 * Gets the fragment
 * @return string const
 */
string SanityUrl::Fragment() const {
    return this->m_fragment;
}
#pragma endregion

#pragma region setters
/**
 * Sets the url scheme
 * @param string scheme
 */
void SanityUrl::SetScheme(string scheme) {
    if(
        scheme != SanityUrl::SCHEME_HTTP &&
        scheme != SanityUrl::SCHEME_HTTPS &&
        scheme != SanityUrl::SCHEME_FTP &&
        scheme != SanityUrl::SCHEME_FTPS &&
        scheme != SanityUrl::SCHEME_FILE
    ) {
        throw InvalidSchemeException();
    } else {
        this->m_scheme = scheme;
    }
}

/**
 * Sets the url hostname
 * @param string hostname
 */
void SanityUrl::SetHostname(string hostname) {
    if(regex_match(hostname, SanityUrl::RX_HOSTNAME)) {
        this->m_hostname = hostname;
    } else {
        throw InvalidHostnameException();
    }
}

/**
 * Sets the url port
 * @param unsigned int port
 */
void SanityUrl::SetPort(unsigned int port) {
    if(
        port > 0 &&
        port <= 65535
    ) {
        this->m_port = port;
    } else {
        throw InvalidPortException();
    }
}

/**
 * Pushes a path part to the url
 * @param string path
 */
void SanityUrl::PushPath(string path) {
    this->m_path.push_back(path);
}

/**
 * Pops a path back out
 */
void SanityUrl::PopPath() {
    this->m_path.pop_back();
}

/**
 * Inserts a query part
 * @param string name
 * @param string value
 */
void SanityUrl::InsertQueryPart(string name, string value) {
    this->m_query.insert(pair<string, string>(name, value));
}

/**
 * Removes a query part
 * @param string name
 */
void SanityUrl::RemoveQueryPart(string name) {
    this->m_query.erase(name);
}

/**
 * Sets the url fragment
 * @param string fragment
 */
void SanityUrl::SetFragment(string fragment) {
    this->m_fragment = fragment;
}
#pragma endregion

/**
 * Creates a clone of the url object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityUrl::clone() const {
    SanityUrl* url = new SanityUrl();
    url->m_scheme = this->m_scheme;
    url->m_hostname = this->m_hostname;
    url->m_port = this->m_port;
    url->m_fragment = this->m_fragment;
    for(auto part : this->m_path) {
        url->PushPath(part);
    }
    for(auto part : this->m_query) {
        url->InsertQueryPart(part.first, part.second);
    }
    return url;
}

/**
 * Builds the url
 * @return string const
 */
string SanityUrl::build() const {
    string path = SanityString::Join(this->m_path, "/");

    string query = "";
    for(auto part : this->m_query) {
        if(!query.empty()) {
            query = query + "&";
        }
        string key = part.first;
        key = curl_easy_escape(nullptr, key.c_str(), strlen(key.c_str()));
        string value = part.second;
        value = curl_easy_escape(nullptr, value.c_str(), strlen(value.c_str()));
        query = query + key + "=" + value;
    }

    string port = (this->m_port == 0 ? "" : ":" + to_string(this->m_port));
    path = path.empty() ? "" : "/" + path;
    query = query.empty() ? "" : "?" + query;
    string fragment = (this->m_fragment != "" ? "#" + this->m_fragment : "");

    return this->Scheme() + "://" + this->m_hostname + port + path + query + fragment;
}
