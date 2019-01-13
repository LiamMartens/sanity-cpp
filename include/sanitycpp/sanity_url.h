#ifndef SANITY_URL_H
#define SANITY_URL_H

#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <regex>
#include <curl/curl.h>
#include "sanity_string.h"
#include "sanity_part_builder.h"

using namespace std;

struct InvalidSchemeException
    : public exception {
    const char* what() const throw() {
        return "Invalid scheme";
    }
};

struct NoSchemeException
    : public exception {
    const char* what() const throw() {
        return "No scheme";
    }
};

struct InvalidPortException
    : public exception {
    const char* what() const throw() {
        return "Invalid port range";
    }
};

struct InvalidHostnameException
    : public exception {
    const char* what() const throw() {
        return "Invalid hostname";
    }
};

struct InvalidPathException
    : public exception {
    const char* what() const throw() {
        return "Invalid path";
    }
};

enum class SanityUrlScheme {
    HTTP = 1,
    HTTPS,
    FTP,
    FTPS,
    FILE
};

class SanityUrl : public SanityPartBuilder {
private:
    /** @var The url scheme */
    string m_scheme = SanityUrl::SCHEME_HTTP;
    /** @var The hostname */
    string m_hostname = "";
    /** @var The port to use */
    unsigned int m_port = 0;
    /** @var The path parts */
    vector<string> m_path;
    /** @var The query string parts */
    map<string, string> m_query;
    /** @var The fragment */
    string m_fragment = "";
public:
    #pragma region scheme constants
    static const string SCHEME_HTTP;
    static const string SCHEME_HTTPS;
    static const string SCHEME_FTP;
    static const string SCHEME_FTPS;
    static const string SCHEME_FILE;
    #pragma endregion

    #pragma region regexes
    static const regex RX_HOSTNAME;
    #pragma endregion

    #pragma region constructors
    SanityUrl();
    SanityUrl(string parse);
    SanityUrl(const SanityUrl& url);
    SanityUrl& operator=(const SanityUrl& url) =default;
    #pragma endregion

    #pragma region getters
    string Scheme() const;
    string Hostname() const;
    unsigned int Port() const;
    vector<string> Path() const;
    map<string, string> Query() const;
    string Fragment() const;
    #pragma endregion

    #pragma region setters
    void SetScheme(string scheme);
    void SetHostname(string hostname);
    void SetPort(unsigned int port);
    void PushPath(string path);
    void PopPath();
    void InsertQueryPart(string name, string value);
    void RemoveQueryPart(string name);
    void SetFragment(string fragment);
    #pragma endregion

    SanityPartBuilder* clone() const override;
    string build() const override;
};

#endif // SANITY_URL_H
