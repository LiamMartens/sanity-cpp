#ifndef SANITY_CLIENT_H
#define SANITY_CLIENT_H

#include <string>
#include <stdio.h>
#include <curl/curl.h>

#include "sanity_request.h"

using namespace std;

class SanityClient
{
    const int MAX_URL_LENGTH = 2083;
    const int API_VERSION = 1;
    const string API_URL = "https://%s.api.sanity.io/v%d/%s";
    const string APICDN_URL = "https://%s.apicdn.sanity.io/v%d/%s";

private:
    /** @var defines the project id for this client */
    string m_project = "";
    /** @var defines the token to use for this client */
    string m_token = "";
    /** @var Defines whether to use the cdn url */
    bool m_use_cdn = false;

protected:
    SanityRequest request(string path, bool useCdn = true);

public:
    SanityClient(string project);
    SanityClient(string project, string token);
    SanityClient(string project, string token, bool useCdn);

    string ApiUrl(string path = "") const;
    string ApiCdnUrl(string path = "") const;
};

#endif // SANITY_CLIENT_H