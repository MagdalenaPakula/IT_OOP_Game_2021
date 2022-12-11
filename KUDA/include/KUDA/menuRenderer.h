#ifndef GAME_MENURENDERER_H
#define GAME_MENURENDERER_H

#include <memory>
#include <SFML/graphics.hpp>
#include "renderer.h"

namespace KUDA
{
    class MenuRenderer : public Renderer
    {
    private:
        float titlePosition = 0.f;
        float itemsPosition = 0.f;
        bool needsRecalculation = true;
        std::unique_ptr<sf::Transformable> background;
        std::unique_ptr<sf::Texture> backgroundTexture;
        std::unique_ptr<sf::Transformable> title;
        std::unique_ptr<sf::Texture> titleTexture;
        sf::Font font;

        void Recalculate();

        void DrawBackground();

        void DrawTitle();

        void DrawMenuItems();

    public:
        std::vector<std::string> menuItems;
        unsigned int selectedItem = 0;
        int fontSize;
        sf::Color defaultColor = { 128, 128, 128 };
        sf::Color highlightColor = { 255, 255, 255 };
    public:

        explicit MenuRenderer( const std::string& fontPath, int fontSize );

        void DrawFrame() override;

        void SetBackground( sf::Color color, float opacity );

        void SetBackground( const std::string& texturePath, float opacity );

        void TitleFromSting( const std::string& titleText, int fontSize );

        void TitleFromImage( const std::string& path, int width, int height );
    };
}


#endif //GAME_MENURENDERER_H
