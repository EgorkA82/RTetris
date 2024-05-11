//
// Created by Иван on 27.04.2024.
//
#include <iostream>

#include "Application.h"
#include "Assets.h"
#include "Screen/Menu.h"
#include "Screen/Settings.h"
#include "UI/SwitchButton.h"

bool Settings::settingsActive = false;

Settings::Settings()
{
    settingsActive = true;

    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        sf::Vector2f(200, 50), "Main menu", Assets::getInstance().font, 30, []
        {
            auto s = new Menu();
            Application::getInstance().setCurrentScreen(s);
            settingsActive = false;
        });
    exitButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    exitButton->setTextColor(sf::Color(255, 255, 255));

    std::map<std::string, std::function<void(void )>> callBacks{
        {"1", []{std::cout<<1<<'\n';}}, {"2", []{std::cout<<2<<'\n';}}, {"3", []{std::cout<<3<<'\n';}}
    };

    std::unique_ptr<SwitchButton> resolutionButton = std::make_unique<SwitchButton>(
        sf::Vector2f(0, 50), sf::Vector2f(200, 50), "Resolution", Assets::getInstance().font, 30, callBacks);
    resolutionButton->setBackgroundColor(sf::Color(160, 160, 160), sf::Color(50, 50, 50), sf::Color(90, 90, 90));
    resolutionButton->setTextColor(sf::Color(255, 255, 255));

    buttons.push_back(std::move(exitButton));
    buttons.push_back(std::move(resolutionButton)); // std::move обязателен для передачи умного указателя в вектор
}

void Settings::handleEvent(const sf::Event &event)
{
    for (auto &button : buttons)// передача события каждой кнопке для его обработки
    {
        if(settingsActive){//чтобы кнопки перестали обрабатываться, если меню настроек не является текущим экраном
            button->handleEvent(event);
        }
        else{
            break;
        }
    }
}

void Settings::update(){}

void Settings::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // учет трансформаций экрана при отрисовке всех ее элементов

    for (auto &button : buttons) // отрисовка всех кнопок
        target.draw(*button, states);
}
bool Settings::isSettingsActive()
{
    return settingsActive;
}
void Settings::setSettingsActive(bool active)
{
    Settings::settingsActive = active;
}
