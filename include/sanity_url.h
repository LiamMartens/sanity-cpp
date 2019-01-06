#ifndef URL
#define URL

#include <string>
#include <vector>
#include <map>
#include <regex>
#include <cstring>
#include <curl/curl.h>

#include "sanity_part_builder.h"

using namespace std;

struct InvalidSchemeException
    : public exception {
    const char* what() const throw() {
        return "Invalid scheme";
    }
};

struct InvalidHostnameException
    : public exception {
    const char* what() const throw() {
        return "Invalid hostname";
    }
};

struct InvalidPortException
    : public exception {
    const char* what() const throw() {
        return "Invalid port (0-65535)";
    }
};

class SanityUrl : public SanityPartBuilder {

    const string SCHEME_HTTP = "http";
    const string SCHEME_HTTPS = "https";
    const string SCHEME_FTP = "ftp";
    const string SCHEME_FTPS = "ftps";
    const string SCHEME_FILE = "file";

    const regex RX_HOSTNAME = regex("([a-zA-Z0-9]+\\.)+([a-zA-Z0-9]+)");

private:
    string m_scheme = SanityUrl::SCHEME_HTTP;
    string m_hostname = "";
    unsigned int m_port = 0;
    vector<string> m_path;
    map<string, string> m_query;
    string m_fragment = "";

public:
    SanityUrl();

    string Scheme();
    string Hostname();
    unsigned int Port();
    vector<string> Path();
    map<string, string> Query();
    string Fragment();

    void SetScheme(string scheme);
    void SetHostname(string hostname);
    void SetPort(unsigned int port);

    void PushPath(string path);
    void PopPath();

    void InsertQueryPart(string name, string value);
    void RemoveQueryPart(string name);

    void SetFragment(string fragment);

    SanityPartBuilder* clone() const;
    string build() const override;
};

#endif // URL