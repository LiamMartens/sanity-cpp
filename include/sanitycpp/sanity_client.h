#ifndef SANITY_CLIENT_H
#define SANITY_CLIENT_H

#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "sanity_request.h"
#include "sanity_query.h"
#include "sanity_create.h"
#include "sanity_patch.h"
#include "sanity_delete.h"
#include "sanity_mutation.h"
#include "sanity_mutations.h"

using json = nlohmann::json;
using namespace std;

#pragma region exceptions
struct NoProjectException
    : public exception {
    const char* what() const throw() {
        return "No project ID";
    }
};

struct NoDataset
    : public exception {
    const char* what() const throw() {
        return "No dataset";
    }
};
#pragma endregion

class SanityClient
{
    const int MAX_URL_LENGTH = 2083;
    const int API_VERSION = 1;
    const string API_URL = "https://%s.api.sanity.io/v%d/%s/%s";
    const string APICDN_URL = "https://%s.apicdn.sanity.io/v%d/%s/%s";

private:
    /** @var defines the project id for this client */
    string m_project = "";
    /** @var defines the token to use for this client */
    string m_token = "";
    /** @var defines the dataset to use */
    string m_dataset;
    /** @var Defines whether to use the cdn url */
    bool m_use_cdn = false;

public:
    #pragma region constructors
    SanityClient(string project, string dataset);
    SanityClient(string project, string dataset, string token);
    SanityClient(string project, string dataset, string token, bool useCdn);
    #pragma endregion

    #pragma region setters
    string ApiUrl(string path = "") const;
    string ApiCdnUrl(string path = "") const;
    void SetProject(string project);
    void SetDataset(string dataset);
    void SetToken(string token);
    void UseCdn(bool useCdn = true);
    #pragma endregion

    SanityRequest* query(const SanityQuery& query) const;
    SanityRequest* mutate(const SanityMutations& mut) const;
    SanityRequest* upload(string file, string mime_type) const;
};

#endif // SANITY_CLIENT_H