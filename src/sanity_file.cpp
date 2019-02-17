#include "sanity_file.h"

SanityFile::SanityFile() {
    this->SetType(this->Type());
}

SanityFile::SanityFile(json from) : SanityObject(from, this->Type()) {
    this->Update(from);
}

SanityFile::SanityFile(const SanityFile& file) : SanityFile(file.toJson()) {}

/**
 * @brief Downloads the file
 * 
 * @param dst 
 */
void SanityFile::Download(string dst) {
    string url = this->Url();
    if(!url.empty()) {
        SanityRequest req(url);
        req.DontStoreInMem();
        req.SetWhenDone([](SanityRequestResponse r) {
            string* d = (string*)r.Userdata;
            ifstream src(r.Body, ios::binary);
            ofstream dest(*d, ios::binary);
            dest << src.rdbuf();
            src.close();
            dest.close();
            delete d;
        });
        thread t = req.perform((void*)new string(dst));
        t.join();
    }
}

/**
 * @brief Uploads a file
 * if successfull will update this object
 * 
 * @param file 
 */
void SanityFile::Upload(string file) {
    
}

#pragma region getters
/**
 * @brief Gets the enforced type
 * 
 * @return string 
 */
string SanityFile::Type() const {
    return "sanity.fileAsset";
}

/**
 * @brief Gets the asset id
 * 
 * @return string 
 */
string SanityFile::AssetId() const {
    return this->m_asset_id;
}

/**
 * @brief Gets the extension
 * 
 * @return string 
 */
string SanityFile::Extension() const {
    return this->m_extension;
}

/**
 * @brief Gets the mime type
 * 
 * @return string 
 */
string SanityFile::MimeType() const {
    return this->m_mime_type;
}

/**
 * @brief Gets the original filename
 * 
 * @return string 
 */
string SanityFile::OriginalFilename() const {
    return this->m_original_filename;
}

/**
 * @brief Sets the path
 * 
 * @return string 
 */
string SanityFile::Path() const {
    return this->m_path;
}

/**
 * @brief Gets the SHA1 hash
 * 
 * @return string 
 */
string SanityFile::Hash() const {
    return this->m_hash;
}

/**
 * @brief Gets the file size in bytes
 * 
 * @return unsigned long 
 */
unsigned long SanityFile::Size() const {
    return this->m_size;
}

/**
 * @brief Gets the url
 * 
 * @return string 
 */
string SanityFile::Url() const {
    return this->m_url;
}
#pragma endregion

#pragma region setters
/**
 * @brief Sets the asset id
 * 
 * @param id 
 */
void SanityFile::SetAssetId(string id) {
    if(regex_match(id, regex("^[a-zA-Z0-9]+$"))) {
        this->m_asset_id = id;
    } else {
        throw SanityFile_InvalidAssetId();
    }
}

/**
 * @brief Sets the file extension
 * 
 * @param ext 
 */
void SanityFile::SetExtension(string ext) {
    this->m_extension = ext;
}

/**
 * @brief Sets the file mime type
 * 
 * @param mime 
 */
void SanityFile::SetMimeType(string mime) {
    if(regex_match(mime, regex("^[a-z0-9.+-]+\\/[a-z0-9.+-]+$"))) {
        this->m_mime_type = mime;
    } else {
        throw SanityFile_InvalidMimeType();
    }
}

/**
 * @brief Sets the original filename
 * 
 * @param filename 
 */
void SanityFile::SetOriginalFilename(string filename) {
    this->m_original_filename = filename;
}

/**
 * @brief Sets the file path
 * 
 * @param path 
 */
void SanityFile::SetPath(string path) {
    this->m_path = path;
}

/**
 * @brief Sets the file hash
 * 
 * @param hash 
 */
void SanityFile::SetHash(string hash) {
    this->m_hash = hash;
}

/**
 * @brief Sets the file size
 * 
 * @param size 
 */
void SanityFile::SetSize(unsigned long size) {
    this->m_size = size;
}

/**
 * @brief Sets the file url
 * 
 * @param url 
 */
void SanityFile::SetUrl(string url) {
    this->m_url = url;
}
#pragma endregion

#pragma region overrides
/**
 * @brief Updates the object from json
 * 
 * @param from 
 */
void SanityFile::Update(json from) {
    SanityObject::Update(from);

    json::iterator end = from.end();

    if(from.find("assetId") != end) {
        this->SetAssetId(from["assetId"].get<string>());
    }

    if(from.find("extension") != end) {
        this->SetExtension(from["extension"].get<string>());
    }

    if(from.find("mimeType") != end) {
        this->SetMimeType(from["mimeType"].get<string>());
    }

    if(from.find("originalFilename") != end) {
        this->SetOriginalFilename(from["originalFilename"].get<string>());
    }

    if(from.find("path") != end) {
        this->SetPath(from["path"].get<string>());
    }

    if(from.find("sha1hash") != end) {
        this->SetHash(from["sha1hash"].get<string>());
    }

    if(from.find("size") != end) {
        this->SetSize(from["size"].get<unsigned long>());
    }

    if(from.find("url") != end) {
        this->SetUrl(from["url"].get<string>());
    }
}

/**
 * @brief Gets a json equivalent of the object
 * 
 * @return json 
 */
json SanityFile::toJson() const {
    json obj = SanityObject::toJson();
    obj["assetId"] = this->AssetId();
    obj["extension"] = this->Extension();
    obj["mimeType"] = this->MimeType();
    obj["originalFilename"] = this->OriginalFilename();
    obj["path"] = this->Path();
    obj["sha1hash"] = this->Hash();
    obj["size"] = this->Size();
    obj["url"] = this->Url();
    return obj;
}

/**
 * @brief Explicit clone
 * 
 * @return SanityObject* 
 */
SanityObject* SanityFile::clone() const {
    return new SanityFile(*this);
}
#pragma endregion
