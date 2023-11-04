#pragma once

#define INCLUDE_SDL_TTF
#include "../../SDL_include.h"

#include <string>

#include "Component.h"

class Text : public Component {
public:
    enum TextStyle { SOLID, SHADED, BLENDED };

    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
    ~Text();

    void Update(float dt) override;
    void Render() override;

    bool Is(const std::string& type) const override;

    void SetText(const std::string& text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(const std::string& fontFile);
    void SetFontSize(int fontSize);

private:
    void RemakeTexture();

    std::shared_ptr<TTF_Font> font;
    SDL_Texture* texture;

    std::string& text;
    TextStyle style;
    std::string& fontFile;
    int fontSize;
    SDL_Color color;
};

inline bool Text::Is(const string& type) const {
    return type == "Text";
}