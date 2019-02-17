#ifndef SANITY_FILE_H
#define SANITY_FILE_H

#include <regex>
#include <nlohmann/json.hpp>
#include "sanity_object.h"
#include "sanity_request.h"

using json = nlohmann::json;
using namespace std;

#pragma region exceptions
class SanityFile_InvalidAssetId
    : public exception {
    const char* what() const throw() {
        return "Invalid asset ID";
    }
};

class SanityFile_InvalidMimeType
    : public exception {
    const char* what() const throw() {
        return "Invalid mime type";
    }
};
#pragma endregion

class SanityFile
    : public SanityObject {
private:
    /** @var The asset id */
    string m_asset_id;
    /** @var The file extension */
    string m_extension;
    /** @var The file mime type */
    string m_mime_type;
    /** @var The original filename */
    string m_original_filename;
    /** @var The file path */
    string m_path;
    /** @var The sha1 hash */
    string m_hash;
    /** @var The file size in bytes */
    unsigned long m_size;
    /** @var The file url */
    string m_url;
public:
    SanityFile();
    SanityFile(json from);
    SanityFile(const SanityFile& file);

    void Download(string dst);
    void Upload(string file);

    #pragma region getters
    string Type() const override;
    string AssetId() const;
    string Extension() const;
    string MimeType() const;
    string OriginalFilename() const;
    string Path() const;
    string Hash() const;
    unsigned long Size() const;
    string Url() const;
    #pragma endregion

    #pragma region setters
    void SetAssetId(string id);
    void SetExtension(string ext);
    void SetMimeType(string mime);
    void SetOriginalFilename(string filename);
    void SetPath(string path);
    void SetHash(string hash);
    void SetSize(unsigned long size);
    void SetUrl(string url);
    #pragma endregion

    #pragma region overrides
    void Update(json from) override;
    json toJson() const override;
    SanityObject* clone() const override;
    #pragma endregion
};

#endif // SANITY_FILE_H
