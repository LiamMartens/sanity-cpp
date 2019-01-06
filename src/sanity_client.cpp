#include "sanity_client.h"
#include "sanity_request.h"

SanityClient::SanityClient(string project) {
    this->m_project = project;
}

SanityClient::SanityClient(string project, string token)
    : SanityClient(project) {
    this->m_token = token;
}

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
        path.c_str()
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
        path.c_str()
    );
    return string(buff);
}
#pragma endregion

#pragma region request handling
SanityRequest SanityClient::request(string path, bool useCdn) {
    SanityRequest req(
        useCdn ? this->ApiCdnUrl(path) : this->ApiUrl(path),
        this->m_token
    );

    return req;
}
#pragma endregion
