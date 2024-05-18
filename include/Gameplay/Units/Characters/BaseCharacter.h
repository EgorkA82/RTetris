#ifndef BASE_CHARACTERS_H
#define BASE_CHARACTERS_H

#include <cstdint>
#include <deque>
#include <functional>
#include <map>
#include <memory>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Gameplay/Units/BaseUnit.h"

/// @brief Свойства действия
class ActionProperties
{
  public:
    sf::Time animationTimeout; // таймаут переключения кадра
    uint8_t frames; // число кадров

    ActionProperties(sf::Time animationTimeout, uint8_t frames);
    ActionProperties() : ActionProperties(sf::Time(), 0)
    {
    }
};

/// @brief Базовый класс персонажа
class BaseCharacter : public BaseUnit
{
  private:
    static const unsigned int initialHP = 100;
    static const unsigned int damage = 20;

  protected:
    enum class Action // текущее действие
    {
        Idle,
        Walk,
        Attack
    };

    enum class Direction // направление взгляда
    {
        Down,
        Up,
        Right,
        Left
    };

    std::map<Action, ActionProperties> animationProperties{
        {Action::Idle, {sf::milliseconds(1000), 2}},
        {Action::Walk, {sf::milliseconds(200), 4}},
        {Action::Attack, {sf::milliseconds(200), 3}}};

    float speed = 3.f; // скорость перемещения - число проходимых за секунду клеток
    std::deque<sf::Vector2u> path; // текущий маршрут

    const sf::Texture &texture = Assets::getInstance().defaultCharacter;

    Action action = Action::Idle;          // текущее действие
    Direction direction = Direction::Down; // направление взгляда

    uint8_t animationFrame = 0; // кадр анимации
    sf::Clock animationClock;   // таймер переключения кадров

    std::jthread movementThread; // поток перемещения
    std::jthread attackThread;   // поток атаки

  public:
    BaseCharacter(sf::Vector2u position, unsigned int hp = initialHP);
    ~BaseCharacter() = default; // требуется для умного указателя

    virtual void moveTo(sf::Vector2u targetPosition, std::function<bool(sf::Vector2u)> isTileFree,
                        bool attackThreadClosureRequired = true,
                        bool stopAtNeighborTile = false); // перемещение в указанную позицию
    virtual void attack(std::unique_ptr<BaseUnit> &targetUnit, std::function<bool(sf::Vector2u)> isTileFree);

    virtual float getSpeed() const;
    virtual void setSpeed(float speed);
    virtual std::deque<sf::Vector2u> getPath() const;
    virtual void setPath(std::deque<sf::Vector2u> path);

    void stopMovementThread();
    void stopAttackThread();

    virtual void update(); // обновление состояний
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override; // отрисовка клетки

    static Direction getDirection(sf::Vector2u fromPoint, sf::Vector2u toPoint);
};

#endif