#include "sanity_image.h"

#pragma region SanityImageDimensions
SanityImageDimensions::SanityImageDimensions() {
    this->SetType(this->Type());
}

SanityImageDimensions::SanityImageDimensions(json from)
    : SanityObject(from, this->Type()) {
    this->Update(from);
}

SanityImageDimensions::SanityImageDimensions(const SanityImageDimensions& dim)
    : SanityImageDimensions(dim.toJson()) {}

#pragma region getters
/**
 * @brief Gets the enforced type
 * 
 * @return string 
 */
string SanityImageDimensions::Type() const {
    return "sanity.imageDimensions";
}

/**
 * @brief Gets the aspect ratio
 * 
 * @return double 
 */
double SanityImageDimensions::AspectRatio() const {
    return this->m_aspect_ratio;
}

/**
 * @brief Gets the width
 * 
 * @return unsigned int 
 */
unsigned int SanityImageDimensions::Width() const {
    return this->m_width;
}

/**
 * @brief Gets the height
 * 
 * @return unsigned int 
 */
unsigned int SanityImageDimensions::Height() const {
    return this->m_height;
}
#pragma endregion

#pragma region setters
/**
 * @brief Sets the aspect ratio
 * 
 * @param ratio 
 */
void SanityImageDimensions::SetAspectRatio(double ratio) {
    this->m_aspect_ratio = ratio;
}

/**
 * @brief Sets the aspect ratio based on the width and height
 */
void SanityImageDimensions::CalcAspectRatio() {
    this->m_aspect_ratio = (double)this->Width() / (double)this->Height();
}

/**
 * @brief Sets the width
 * 
 * @param width 
 */
void SanityImageDimensions::SetWidth(unsigned int width) {
    this->m_width = width;
}

/**
 * @brief Sets the height
 * 
 * @param height 
 */
void SanityImageDimensions::SetHeight(unsigned int height) {
    this->m_height = height;
}
#pragma endregion

#pragma region overrides
/**
 * @brief Updates from a json object
 * 
 * @param from 
 */
void SanityImageDimensions::Update(json from) {
    SanityObject::Update(from);
    json::iterator end = from.end();
    if(from.find("aspectRatio") != end) {
        this->SetAspectRatio(from["aspectRatio"].get<double>());
    }
    if(from.find("width") != end) {
        this->SetWidth(from["width"].get<unsigned int>());
    }
    if(from.find("height") != end) {
        this->SetHeight(from["height"].get<unsigned int>());
    }
}

/**
 * @brief Converts the object to json
 * 
 * @return json 
 */
json SanityImageDimensions::toJson() const {
    json obj = SanityObject::toJson();
    obj["aspectRatio"] = this->AspectRatio();
    obj["width"] = this->Width();
    obj["height"] = this->Height();
    return obj;
}

/**
 * @brief Creates a clone of the object
 * 
 * @return SanityObject* 
 */
SanityObject* SanityImageDimensions::clone() const {
    return new SanityImageDimensions(*this);
}
#pragma endregion
#pragma endregion

#pragma region SanityImagePaletteSwatch
SanityImagePaletteSwatch::SanityImagePaletteSwatch()
    : SanityObject(this->Type()) {
}

SanityImagePaletteSwatch::SanityImagePaletteSwatch(json from)
    : SanityObject(from, this->Type()) {
    this->Update(from);
}

SanityImagePaletteSwatch::SanityImagePaletteSwatch(const SanityImagePaletteSwatch& sw)
    : SanityImagePaletteSwatch(sw.toJson()) {
}
#pragma region getters
/**
 * @brief Gets the enforced type
 * 
 * @return string 
 */
string SanityImagePaletteSwatch::Type() const {
    return "sanity.imagePaletteSwatch";
}

/**
 * @brief Gets the background color
 *
 * @return SanityColor
 */
SanityColor SanityImagePaletteSwatch::Background() const {
    return this->m_background;
}

/**
 * @brief Gets the foreground color
 *
 * @return SanityColor
 */
SanityColor SanityImagePaletteSwatch::Foreground() const {
    return this->m_foreground;
}

/**
 * @brief The title color
 *
 * @return SanityColor
 */
SanityColor SanityImagePaletteSwatch::Title() const {
    return this->m_title;
}

/**
 * @brief Gets the swatch population
 * 
 * @return double
 */
double SanityImagePaletteSwatch::Population() const {
    return this->m_population;
}
#pragma endregion

#pragma region setters
/**
 * @brief Sets the background color
 *
 * @param c
 */
void SanityImagePaletteSwatch::SetBackground(SanityColor c) {
    this->m_background = c;
}

/**
 * @brief Sets the foreground color
 * 
 * @param c 
 */
void SanityImagePaletteSwatch::SetForeground(SanityColor c) {
    this->m_foreground = c;
}

/**
 * @brief Sets the title color
 * 
 * @param c 
 */
void SanityImagePaletteSwatch::SetTitle(SanityColor c) {
    this->m_title = c;
}

/**
 * @brief Sets the swatch population
 * 
 * @param pop 
 */
void SanityImagePaletteSwatch::SetPopulation(double pop) {
    this->m_population = pop;
}
#pragma endregion

#pragma region overrides
/**
 * @brief Updates the swatch from json
 *
 * @param from
 */
void SanityImagePaletteSwatch::Update(json from) {
    json::iterator end = from.end();

    if(from.find("background") != end) {
        this->SetBackground(from["background"].get<string>());
    }

    if(from.find("foreground") != end) {
        this->SetForeground(from["foreground"].get<string>());
    }

    if(from.find("title") != end) {
        this->SetTitle(from["title"].get<string>());
    }

    if(from.find("population") != end) {
        this->SetPopulation(from["population"].get<double>());
    }
}

/**
 * @brief Converts to json
 *
 * @return json
 */
json SanityImagePaletteSwatch::toJson() const {
    json obj = SanityObject::toJson();
    obj["background"] = this->m_background.Hex();
    obj["foreground"] = this->m_foreground.Hex();
    obj["title"] = this->m_title.Hex();
    obj["population"] = this->m_population;
    return obj;
}

/**
 * @brief Creates a clone of the object
 *
 * @return SanityObject*
 */
SanityObject* SanityImagePaletteSwatch::clone() const {
    return new SanityImagePaletteSwatch(*this);
}
#pragma endregion
#pragma endregion

#pragma region SanityImagePalette
SanityImagePalette::SanityImagePalette() : SanityObject(this->Type()) {}
SanityImagePalette::SanityImagePalette(json from)
    : SanityObject(from, this->Type()) {
    this->Update(from);
}
SanityImagePalette::SanityImagePalette(const SanityImagePalette& p)
    : SanityImagePalette(p.toJson()) {
}
#pragma region getters
/**
 * @brief Gets the enforced type
 *
 * @return string
 */
string SanityImagePalette::Type() const {
    return "sanity.imagePalette";
}

/**
 * @brief Gets the complete swatch map
 * 
 * @return map<string, SanityImagePaletteSwatch> 
 */
map<string, SanityImagePaletteSwatch> SanityImagePalette::Swatches() const {
    return this->m_swatches;
}

/**
 * @brief Gets a swatch
 * 
 * @param name
 * @return SanityImagePaletteSwatch
 */
SanityImagePaletteSwatch SanityImagePalette::Swatch(string name) const {
    if(this->m_swatches.find(name) == this->m_swatches.end()) {
        throw SanityImagePalette_SwatchNotFound();
    } else {
        return this->m_swatches.at(name);
    }
}
#pragma endregion

#pragma region setters
/**
 * @brief Replaces the current swatches map
 * 
 * @param swatches 
 */
void SanityImagePalette::SetSwatches(map<string, SanityImagePaletteSwatch> swatches) {
    this->m_swatches = swatches;
}

/**
 * @brief Inserts a swatch
 * 
 * @param name 
 * @param swatch 
 */
void SanityImagePalette::InsertSwatch(string name, SanityImagePaletteSwatch swatch) {
    this->m_swatches.insert(pair<string, SanityImagePaletteSwatch>(name, swatch));
}

/**
 * @brief Removes swatch
 * 
 * @param name 
 */
void SanityImagePalette::RemoveSwatch(string name) {
    this->m_swatches.erase(name);
}

/**
 * @brief Resets the palette
 */
void SanityImagePalette::Reset() {
    this->m_swatches.clear();
}
#pragma endregion

#pragma region overrides
/**
 * @brief Updates the object from json
 *
 * @param from
 */
void SanityImagePalette::Update(json from) {
    json::iterator end = from.end();
    for(auto entry : from.items()) {
        if(entry.key() != "_type") {
            this->InsertSwatch(entry.key(), entry.value());
        }
    }
}

/**
 * @brief Converts the object to json
 * 
 * @return json 
 */
json SanityImagePalette::toJson() const {
    json obj = SanityObject::toJson();
    for(auto entry : this->m_swatches) {
        obj[entry.first] = entry.second.toJson();
    }
    return obj;
}

/**
 * @brief Creates a clone
 * 
 * @return SanityObject* 
 */
SanityObject* SanityImagePalette::clone() const {
    return new SanityImagePalette(*this);
}
#pragma endregion
#pragma endregion

#pragma region SanityImageMetadata
SanityImageMetadata::SanityImageMetadata() : SanityObject(this->Type()) {}
SanityImageMetadata::SanityImageMetadata(json from)
    : SanityObject(from, this->Type()) {
}
SanityImageMetadata::SanityImageMetadata(const SanityImageMetadata& img)
    : SanityImageMetadata(img.toJson()) {
}

#pragma region getters
/**
 * @brief Gets the enforced type
 * 
 * @return string 
 */
string SanityImageMetadata::Type() const {
    return "sanity.imageMetadata";
}

/**
 * @brief Gets the image dimensions object
 * 
 * @return SanityImageDimensions 
 */
SanityImageDimensions SanityImageMetadata::Dimensions() const {
    return this->m_dimensions;
}

/**
 * @brief Gets the lqip base64 url
 * 
 * @return string 
 */
string SanityImageMetadata::Lqip() const {
    return this->m_lqip;
}

/**
 * @brief Gets the palette
 * 
 * @return SanityImagePalette 
 */
SanityImagePalette SanityImageMetadata::Palette() const {
    return this->m_palette;
}
#pragma endregion

#pragma region setters
/**
 * @brief Replaces the current dimensions object
 * 
 * @param dim 
 */
void SanityImageMetadata::SetDimensions(SanityImageDimensions dim) {
    this->m_dimensions = dim;
}

/**
 * @brief Allows direct mutation of the dimensions
 * 
 * @param f 
 */
void SanityImageMetadata::MutateDimensions(void(*f)(SanityImageDimensions*)) {
    f(&this->m_dimensions);
}

/**
 * @brief Sets the lqip base64
 * 
 * @param lqip 
 */
void SanityImageMetadata::SetLqip(string lqip) {
    this->m_lqip = lqip;
}

/**
 * @brief Sets the palette
 * 
 * @param p 
 */
void SanityImageMetadata::SetPalette(SanityImagePalette p) {
    this->m_palette = p;
}

/**
 * @brief Inserts a palette swatch
 * 
 * @param name 
 * @param s 
 */
void SanityImageMetadata::InsertPaletteSwatch(string name, SanityImagePaletteSwatch s) {
    this->m_palette.InsertSwatch(name, s);
}

/**
 * @brief Removes a palette swatch
 * 
 * @param name 
 */
void SanityImageMetadata::RemovePaletteSwatch(string name) {
    this->m_palette.RemoveSwatch(name);
}

/**
 * @brief Resets the palette
 */
void SanityImageMetadata::ResetPalette() {
    this->m_palette.Reset();
}
#pragma endregion

#pragma region overrides
/**
 * @brief Updates the object from json
 * 
 * @param from 
 */
void SanityImageMetadata::Update(json from) {
    SanityObject::Update(from);

    json::iterator end = from.end();

    if(from.find("dimensions") != end) {
        this->SetDimensions(from["dimensions"]);
    }

    if(from.find("lqip") != end) {
        this->SetLqip(from["lqip"].get<string>());
    }

    if(from.find("palette") != end) {
        this->SetPalette(from["palette"]);
    }
}

/**
 * @brief Converts the object to json
 * 
 * @return json 
 */
json SanityImageMetadata::toJson() const {
    json obj = SanityObject::toJson();
    obj["dimensions"] = this->m_dimensions.toJson();
    obj["lqip"] = this->m_lqip;
    obj["palette"] = this->m_palette.toJson();
    return obj;
}

/**
 * @brief Creates a clone of the object
 * 
 * @return SanityObject* 
 */
SanityObject* SanityImageMetadata::clone() const {
    return new SanityImageMetadata(*this);
}
#pragma endregion
#pragma endregion

#pragma region SanityImage
SanityImage::SanityImage() {
    this->SetType(this->Type());
}

SanityImage::SanityImage(json from) : SanityFile(from) {
    this->SetType(this->Type());
}

SanityImage::SanityImage(const SanityImage& image) : SanityImage(image.toJson()) {
}
#pragma region getters
/**
 * @brief Gets the enforced type
 * 
 * @return string 
 */
string SanityImage::Type() const {
    return "sanity.imageAsset";
}

/**
 * @brief Gets the image metadata
 * 
 * @return SanityImageMetadata
 */
SanityImageMetadata SanityImage::Metadata() const {
    return this->m_metadata;
}
#pragma endregion

#pragma region setters
/**
 * @brief Sets the metadata
 * 
 * @param m 
 */
void SanityImage::SetMetadata(SanityImageMetadata m) {
    this->m_metadata = m;
}

/**
 * @brief Allows mutating the metadata object
 * 
 * @param f 
 */
void SanityImage::MutateMetadata(void(*f)(SanityImageMetadata* meta)) {
    f(&this->m_metadata);
}
#pragma endregion

#pragma region overrides
/**
 * @brief Updates from json
 * 
 * @param from 
 */
void SanityImage::Update(json from) {
    SanityFile::Update(from);
    json::iterator end = from.end();
    if(from.find("metadata") != end) {
        this->SetMetadata(from["metadata"]);
    }
}

/**
 * @brief Converts the object to json
 * 
 * @return json 
 */
json SanityImage::toJson() const {
    json obj = SanityFile::toJson();
    obj["metadata"] = this->m_metadata.toJson();
    return obj;
}

/**
 * @brief Creates clone of object
 * 
 * @return SanityObject* 
 */
SanityObject* SanityImage::clone() const {
    return new SanityImage(*this);
}
#pragma endregion
#pragma endregion
