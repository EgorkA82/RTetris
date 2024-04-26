#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>

#include "BaseScreen.h"

/// @brief Экран меню
/// @details Этот экран запускается при запуске приложения
class Menu : public BaseScreen
{
  public:
    Menu();

    virtual void handleEvent(const sf::Event &event) override;
    virtual void update() override;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif