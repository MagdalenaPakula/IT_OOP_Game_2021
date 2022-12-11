#include "menuRenderer.h"

KUDA::MenuRenderer::MenuRenderer( const std::string& fontPath, int fontSize ) : fontSize( fontSize ) {
    if ( !font.loadFromFile( fontPath ))
        throw std::runtime_error( "Could not load font file from " + fontPath );
}

void KUDA::MenuRenderer::Recalculate() {
    if ( auto bgRect = dynamic_cast<sf::RectangleShape*>(background.get())) {
        bgRect->setSize( sf::Vector2f( static_cast<float>( window.lock()->GetWidth()),
                                       static_cast<float>(window.lock()->GetHeight())));
    } else if ( auto bgSprite = dynamic_cast<sf::Sprite*>(background.get())) {
        auto[textureWidth, textureHeight] = titleTexture->getSize();
        bgSprite->setScale( static_cast<float>(window.lock()->GetWidth()) / static_cast<float>(textureWidth),
                            static_cast<float>(window.lock()->GetHeight()) / static_cast<float>(textureHeight));
    }

    int titleHeight;
    if ( auto titleText = dynamic_cast<sf::Text*>(title.get()))
        titleHeight = static_cast<int>(titleText->getLocalBounds().height);
    else if ( auto titleSprite = dynamic_cast<sf::Sprite*>(title.get()))
        titleHeight = static_cast<int>(titleSprite->getLocalBounds().height);
    else
        throw std::runtime_error( "Title has invalid type" );

    int totalHeight = static_cast<int>(( titleHeight * 2 ) + (int) ( fontSize * ( menuItems.size() + 1 )) + (int) ( 0.5f * (float) fontSize * (float) ( menuItems.size() - 1 )));
    auto padding = static_cast<float>(( window.lock()->GetHeight() - totalHeight )) / 2;
    titlePosition = padding + static_cast<float>( 0.5 * titleHeight );
    itemsPosition = padding + static_cast<float>(( titleHeight * 2 ) + fontSize * 1.5);
    needsRecalculation = false;
}

void KUDA::MenuRenderer::DrawBackground() {
    auto& r = *dynamic_cast<sf::Drawable*>(background.get());
    window.lock()->Draw( r );
}

void KUDA::MenuRenderer::DrawTitle() {
    window.lock()->Draw( *dynamic_cast<sf::Drawable*>(background.get()));
    title->setPosition((float) window.lock()->GetWidth() / 2, titlePosition );
    window.lock()->Draw( *dynamic_cast<sf::Drawable*>(title.get()));
}

void KUDA::MenuRenderer::DrawMenuItems() {
    for ( int i = 0; i < menuItems.size(); ++i ) {
        auto item = sf::Text( menuItems[i], font, fontSize );
        item.setFillColor( i == selectedItem ? highlightColor : defaultColor );
        item.setOrigin( item.getLocalBounds().width / 2, item.getLocalBounds().height / 2 );
        item.setPosition( static_cast<float>(window.lock()->GetWidth()) / 2,
                          itemsPosition + static_cast<float>(( fontSize * i * 1.5 )));
        window.lock()->Draw( item );
    }
}

void KUDA::MenuRenderer::DrawFrame() {
    if ( window.expired())
        throw std::runtime_error( "Renderer has no window attached" );
    if ( needsRecalculation )
        Recalculate();
    DrawBackground();
    DrawTitle();
    DrawMenuItems();
}

void KUDA::MenuRenderer::SetBackground( sf::Color color, float opacity ) {
    auto bg = std::make_unique<sf::RectangleShape>();
    if ( opacity > 1.f ) opacity = 1.f;
    if ( opacity < 0.f ) opacity = 0.f;
    color.a = static_cast<uint8_t>(opacity * 255);
    bg->setFillColor( color );
    bg->setPosition( 0, 0 );
    background = std::move( bg );
    backgroundTexture = nullptr;
}

void KUDA::MenuRenderer::SetBackground( const std::string& texturePath, float opacity ) {
    if ( backgroundTexture == nullptr )
        backgroundTexture = std::make_unique<sf::Texture>();
    if ( !backgroundTexture->loadFromFile( texturePath ))
        throw std::runtime_error( "Could not load texture from file " + texturePath );
    needsRecalculation = true;
    auto bg = std::make_unique<sf::Sprite>();
    bg->setTexture( *backgroundTexture );
    auto[textureWidth, textureHeight] = titleTexture->getSize();
    bg->setTextureRect( { 0, 0, (int) textureWidth, (int) textureHeight } );
    bg->setPosition( 0, 0 );
    bg->setColor( { 0xFF, 0xFF, 0xFF, static_cast<uint8_t>(opacity * 255) } );
    background = std::move( bg );
}

void KUDA::MenuRenderer::TitleFromSting( const std::string& titleText, int fontSize ) {
    auto t = std::make_unique<sf::Text>();
    t->setString( titleText );
    t->setCharacterSize( fontSize );
    t->setFont( font );
    t->setOrigin( t->getLocalBounds().width / 2, t->getLocalBounds().height / 2 );
    title = std::move( t );
    titleTexture = nullptr;
}

void KUDA::MenuRenderer::TitleFromImage( const std::string& path, int width, int height ) {
    if ( titleTexture == nullptr )
        titleTexture = std::make_unique<sf::Texture>();
    if ( !titleTexture->loadFromFile( path ))
        throw std::runtime_error( "Could not load texture from file " + path );
    auto t = std::make_unique<sf::Sprite>();
    t->setTexture( *titleTexture );
    auto[textureWidth, textureHeight] = titleTexture->getSize();
    t->setTextureRect( { 0, 0, (int) textureWidth, (int) textureHeight } );
    t->scale( static_cast<float>(width) / static_cast<float>(textureWidth),
              static_cast<float>(height) / static_cast<float>(textureHeight));
    t->setOrigin((float) width / 2, (float) height / 2 );
    title = std::move( t );
}
