#include "Gameplay/Players/Bot.h"
#include "Gameplay/Units/Characters/BaseCharacter.h"

Bot::Bot() : BasePlayer()
{
    auto base = std::make_unique<Base>(sf::Vector2u(18, 18));
    auto character = std::make_unique<BaseCharacter>(sf::Vector2u(17, 17));

    units.push_back(std::move(base));
    units.push_back(std::move(character));
}