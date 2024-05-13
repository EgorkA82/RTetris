#ifndef BASE_UNIT_H
#define BASE_UNIT_H

#include <SFML/Graphics.hpp>

#include "Assets.h"

#define SPRITE_SIZE_PX 16

class BaseUnit : public sf::Drawable, public sf::Transformable
{
  protected:
    enum class Direction // направление взгляда
    {
        Down,
        Up,
        Right,
        Left
    };

    sf::Vector2u position; // позиция в клеточном поле

    const sf::Texture &texture = Assets::getInstance().defaultTexture;
    sf::IntRect area = sf::IntRect(0, 0, SPRITE_SIZE_PX, SPRITE_SIZE_PX); // участок текстуры для отрисовки

    Direction direction = Direction::Down; // направление взгляда

  public:
    BaseUnit(sf::Vector2u position);
    ~BaseUnit() = default; // требуется для умного указателя

    sf::Vector2u getPosition() const;
    void setPosition(sf::Vector2u position);

    virtual sf::IntRect getArea() const; // получение области текстуры - требуется для масштабирования

    virtual void update() = 0; // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0; // отрисовка клетки
};

#endif