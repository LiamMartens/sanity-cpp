#include "sanity_client.h"
#include "sanity_request.h"

#pragma region constructors
SanityClient::SanityClient(string project, string dataset) {
    this->m_project = project;
    this->m_dataset = dataset;
}

SanityClient::SanityClient(string project, string dataset, string token)
    : SanityClient(project, dataset) {
    this->m_token = token;
}

SanityClient::SanityClient(string project, string dataset, string token, bool useCdn)
    : SanityClient(project, dataset, token) {
    this->m_use_cdn = useCdn;
}
#pragma endregion

#pragma region getters
/**
 * Builds an API url
 * @param string path Path to append to the base url
 * @return string
 */
string SanityClient::ApiUrl(string path) const {
    char buff[SanityClient::MAX_URL_LENGTH];
    sprintf(
        buff,
        SanityClient::API_URL.c_str(),
        this->m_project.c_str(),
        SanityClient::API_VERSION,
        path.c_str(),
        this->m_dataset.c_str()
    );
    return string(buff);
}

/**
 * Builds a CDN based API url
 * @param string path Path to append to the base cdn url
 * @return string
 */
string SanityClient::ApiCdnUrl(string path) const {
    char buff[SanityClient::MAX_URL_LENGTH];
    sprintf(
        buff,
        SanityClient::APICDN_URL.c_str(),
        this->m_project.c_str(),
        SanityClient::API_VERSION,
        path.c_str(),
        this->m_dataset.c_str()
    );
    return string(buff);
}

/**
 * Sets the project ID to use
 * @param string project
 */
void SanityClient::SetProject(string project) {
    this->m_project = project;
}

/**
 * Sets the dataset to use
 * @param string dataset
 */
void SanityClient::SetDataset(string dataset) {
    this->m_dataset = dataset;
}

/**
 * Sets the token
 * @param string token
 */
void SanityClient::SetToken(string token) {
    this->m_token = token;
}

/**
 * Enable/disable cdn usage
 * @param bool useCdn
 */
void SanityClient::UseCdn(bool useCdn) {
    this->m_use_cdn = useCdn;
}
#pragma endregion

#pragma region request handling
/**
 * Performs a query
 * @param const SanityQuery& query The query to execute
 * @return json
 */
SanityRequest* SanityClient::query(const SanityQuery& query) {
    string query_path = "data/query";
    SanityUrl url(this->m_use_cdn ? this->ApiCdnUrl(query_path) : this->ApiUrl(query_path));
    url.InsertQueryPart("query", query.build());
    SanityRequest* req = new SanityRequest(url.build(), this->m_token);
    return req;
}
#pragma endregion
