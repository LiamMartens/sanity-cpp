#ifndef SANITY_IMAGE_H
#define SANITY_IMAGE_H

#include <map>
#include <nlohmann/json.hpp>
#include "sanity_color.h"
#include "sanity_file.h"

using json = nlohmann::json;

#pragma region exceptions
class SanityImagePalette_SwatchNotFound
    : public exception {
    const char* what() const throw() {
        return "Palette swatch not found";
    }
};
#pragma endregion

#pragma region SanityImageDimensions
class SanityImageDimensions
    : public SanityObject {
private:
    /** @var The image aspect ratio */
    double m_aspect_ratio = 1;
    /** @var The image width */
    unsigned int m_width = 1;
    /** @var The image height */
    unsigned int m_height = 1;
public:
    SanityImageDimensions();
    SanityImageDimensions(json from);
    SanityImageDimensions(const SanityImageDimensions& dim);

    #pragma region getters
    string Type() const override;
    double AspectRatio() const;
    unsigned int Width() const;
    unsigned int Height() const;
    #pragma endregion

    #pragma region setters
    void SetAspectRatio(double ratio);
    void CalcAspectRatio();
    void SetWidth(unsigned int width);
    void SetHeight(unsigned int height);
    #pragma endregion

    #pragma region overrides
    void Update(json from) override;
    json SharedJson() const override;
    json SaveObject() const override;
    json toJson() const override;
    SanityObject* clone() const override;
    #pragma endregion
};
#pragma endregion

#pragma region SanityImagePaletteSwatch
class SanityImagePaletteSwatch
    : public SanityObject {
private:
    /** @var The background color */
    SanityColor m_background;
    /** @var The foreground color */
    SanityColor m_foreground;
    /** @var The title color */
    SanityColor m_title;
    /** @var The population of the palette swatch */
    double m_population;
public:
    SanityImagePaletteSwatch();
    SanityImagePaletteSwatch(json from);
    SanityImagePaletteSwatch(const SanityImagePaletteSwatch& sw);

    #pragma region getters
    string Type() const override;
    SanityColor Background() const;
    SanityColor Foreground() const;
    SanityColor Title() const;
    double Population() const;
    #pragma endregion

    #pragma region setters
    void SetBackground(SanityColor c);
    void SetForeground(SanityColor c);
    void SetTitle(SanityColor c);
    void SetPopulation(double pop);
    #pragma endregion

    #pragma region overrides
    void Update(json from) override;
    json SharedJson() const override;
    json SaveObject() const override;
    json toJson() const override;
    SanityObject* clone() const override;
    #pragma endregion
};
#pragma endregion

#pragma region SanityImagePalette
class SanityImagePalette
    : public SanityObject {
private:
    /** @var The palettes */
    map<string, SanityImagePaletteSwatch> m_swatches;
public:
    SanityImagePalette();
    SanityImagePalette(json from);
    SanityImagePalette(const SanityImagePalette& p);

    #pragma region getters
    string Type() const override;
    map<string, SanityImagePaletteSwatch> Swatches() const;
    SanityImagePaletteSwatch Swatch(string name) const;
    #pragma endregion

    #pragma region setters
    void SetSwatches(map<string, SanityImagePaletteSwatch> swatches);
    void InsertSwatch(string name, SanityImagePaletteSwatch swatch);
    void RemoveSwatch(string name);
    void Reset();
    #pragma endregion

    #pragma region overrides
    void Update(json from) override;
    json toJson() const override;
    json SaveObject() const override;
    SanityObject* clone() const override;
    #pragma endregion
};
#pragma endregion

#pragma region SanityImageMetadata
class SanityImageMetadata
    : public SanityObject {
private:
    /** @var The dimensions of the image */
    SanityImageDimensions m_dimensions;
    /** @var Low Quality Image Placeholder base64 url */
    string m_lqip;
    /** @var The image palette */
    SanityImagePalette m_palette;
public:
    SanityImageMetadata();
    SanityImageMetadata(json from);
    SanityImageMetadata(const SanityImageMetadata& img);

    #pragma region getters
    string Type() const override;
    SanityImageDimensions Dimensions() const;
    string Lqip() const;
    SanityImagePalette Palette() const;
    #pragma endregion

    #pragma region setters
    void SetDimensions(SanityImageDimensions dim);
    void MutateDimensions(void(*f)(SanityImageDimensions*));
    void SetLqip(string lqip);
    void SetPalette(SanityImagePalette p);
    void InsertPaletteSwatch(string name, SanityImagePaletteSwatch s);
    void RemovePaletteSwatch(string name);
    void ResetPalette();
    #pragma endregion

    #pragma region overrides
    void Update(json from) override;
    json SharedJson() const override;
    json SaveObject() const override;
    json toJson() const override;
    SanityObject* clone() const override;
    #pragma endregion
};
#pragma endregion

#pragma region SanityImage
class SanityImage
    : public SanityFile {
private:
    /** @var The image metadata */
    SanityImageMetadata m_metadata;
public:
    SanityImage();
    SanityImage(json from);
    SanityImage(const SanityImage& image);

    #pragma region getters
    string Type() const override;
    SanityImageMetadata Metadata() const;
    #pragma endregion

    #pragma region setters
    void SetMetadata(SanityImageMetadata m);
    void MutateMetadata(void(*f)(SanityImageMetadata* meta));
    #pragma endregion

    #pragma region overrides
    void Update(json from) override;
    json toJson() const override;
    json SaveObject() const override;
    SanityObject* clone() const override;
    #pragma endregion
};
#pragma endregion

#endif // SANITY_IMAGE_H