#include "sanity_url.h"

SanityUrl::SanityUrl() {
    this->m_type = SanityPartBuilderType::SURL;
}

/**
 * Returns the current scheme
 * @return string
 */
string SanityUrl::Scheme() {
    return this->m_scheme;
}

/**
 * Returns the current hostname
 * @return string
 */
string SanityUrl::Hostname() {
    return this->m_hostname;
}

/**
 * Returns the current port
 * @return unsigned int
 */
unsigned int SanityUrl::Port() {
    return this->m_port;
}

/**
 * Returns the path vector
 * @return vector<string>
 */
vector<string> SanityUrl::Path() {
    return this->m_path;
}

/**
 * Returns the current query map
 * @return map<string, string>
 */
map<string, string> SanityUrl::Query() {
    return this->m_query;
}

/**
 * Returns the current fragment
 * @return string
 */
string SanityUrl::Fragment() {
    return this->m_fragment;
}

/**
 * Sets the URL scheme
 * @param string scheme The new scheme to set
 * @return Url*
 */
void SanityUrl::SetScheme(string scheme) {
    if (
        scheme == SanityUrl::SCHEME_HTTP ||
        scheme == SanityUrl::SCHEME_HTTPS ||
        scheme == SanityUrl::SCHEME_FTP ||
        scheme == SanityUrl::SCHEME_FTPS ||
        scheme == SanityUrl::SCHEME_FILE
    ) {
        this->m_scheme = scheme;
    } else {
        throw InvalidSchemeException();
    }
}

/**
 * Sets the URL hostname
 * @param string hostname The new hostname
 * @return Url*
 */
void SanityUrl::SetHostname(string hostname) {
    if(regex_match(hostname, SanityUrl::RX_HOSTNAME)) {
        this->m_hostname = hostname;
    } else {
        throw InvalidHostnameException();
    }
}

/**
 * Sets the URL port
 * @param unsigned int port
 * @return Url*
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
 * Pushes a path part
 * @param string path Path part
 * @return Url*
 */
void SanityUrl::PushPath(string path) {
    this->m_path.push_back(path);
}

/**
 * Pops a path part
 * @return Url*
 */
void SanityUrl::PopPath() {
    this->m_path.pop_back();
}

/**
 * Inserts query part
 * @param string name Name of the query part
 * @param string value Value of the query part
 * @return Url*
 */
void SanityUrl::InsertQueryPart(string name, string value) {
    this->m_query.insert(pair<string, string>(name, value));
}

/**
 * Removes  a query part
 * @param string name Name of the query part to remove
 * @return Url*
 */
void SanityUrl::RemoveQueryPart(string name) {
    this->m_query.erase(name);
}

/**
 * Sets the url fragment
 * @param string fragment The new fragment
 * @return Url*
 */
void SanityUrl::SetFragment(string fragment) {
    this->m_fragment = fragment;
}

/**
 * Creates a copy of the url object
 * @return SanityPartBuilder* const
 */
SanityPartBuilder* SanityUrl::clone() const {
    return new SanityUrl(*this);
}

/**
 * Builds the URL
 * @return string const
 */
string SanityUrl::build() const {
    string path = "";
    vector<string>::const_iterator path_it;
    for(
        path_it = this->m_path.begin();
        path_it != this->m_path.end();
        ++path_it
    ) {
        path += "/" + *path_it;
    }

    // build query string
    string query = "";
    map<string, string>::const_iterator query_it;
    for(
        query_it = this->m_query.begin();
        query_it != this->m_query.end();
        ++query_it
    ) {
        if(query != "") {
            query += "&";
        }
        string key = (*query_it).first;
        key = curl_easy_escape(nullptr, key.c_str(), strlen(key.c_str()));
        string value = (*query_it).second;
        value = curl_easy_escape(nullptr, value.c_str(), strlen(value.c_str()));
        query += key + "=" + value;
    }

    return
        this->m_scheme +
        "://" +
        this->m_hostname +
        (this->m_port == 0 ? "" : ":" + to_string(this->m_port)) +
        path +
        "?" + query +
        (this->m_fragment != "" ? "#" + this->m_fragment : "");
}