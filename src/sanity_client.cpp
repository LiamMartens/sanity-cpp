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
 * @return SanityRequest*
 */
SanityRequest* SanityClient::query(const SanityQuery& query) const {
    string path = "data/query";
    SanityUrl url(this->m_use_cdn ? this->ApiCdnUrl(path) : this->ApiUrl(path));
    url.InsertQueryPart("query", query.build());
    SanityRequest* req = new SanityRequest(url.build(), this->m_token);
    return req;
}

/**
 * Ceates a mutation request
 * @param const SanityMutation& mut
 * @return SanityRequest*
 */
SanityRequest* SanityClient::mutate(const SanityMutations& mut) const {
    string path = "data/mutate";
    SanityUrl url(this->m_use_cdn ? this->ApiCdnUrl(path) : this->ApiUrl(path));
    SanityRequest* req = new SanityRequest(url.build(), this->m_token);
    req->SetMethod(SanityRequestMethod::POST);
    req->SetData(mut);
    return req;
}

/**
 * @brief Uploads a file
 * 
 * @param file 
 * @return SanityRequest* 
 */
SanityRequest* SanityClient::upload(string file, string mime_type) const {
    string path = mime_type.substr(0, 6) == "image/" ? "assets/images" : "assets/files";
    SanityUrl url(this->ApiUrl(path));
    SanityRequest* req = new SanityRequest(url.build(), this->m_token);
    req->SetMethod(SanityRequestMethod::POST);
    req->SetUploadFile(file, mime_type);
    return req;
}
#pragma endregion
