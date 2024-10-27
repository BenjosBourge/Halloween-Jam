/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include "../../include/core/coordinator.hpp"

void Coordinator::loadTextures()
{
    _font.loadFromFile("assets/neon_pixel-7.ttf");

    sf::Texture texture;
    texture.loadFromFile("assets/blank_square.png");
    _textures.emplace_back(TEXTURE_TYPE_EXAMPLE, texture);

    texture.loadFromFile("assets/rail.png");
    _textures.emplace_back(TEXTURE_TYPE_RAIL, texture);

    texture.loadFromFile("assets/middleGround.png");
    _textures.emplace_back(TEXTURE_TYPE_MIDDLEGROUND, texture);

    texture.loadFromFile("assets/backGround.png");
    _textures.emplace_back(TEXTURE_TYPE_BACKGROUND, texture);

    texture.loadFromFile("assets/moon.png");
    _textures.emplace_back(TEXTURE_TYPE_MOON, texture);
}