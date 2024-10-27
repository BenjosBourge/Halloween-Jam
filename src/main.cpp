/*------------------------*
 * ECS by Benjamin Bourge *
 *------------------------*/

#include <iostream>
#include <vector>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "../include/core/coordinator.hpp"
#include "../include/core/ecs.hpp"
#include "../include/core/texture.hpp"
#include "../include/core/components/transform.hpp"
#include "../include/core/components/spriteRenderer.hpp"
#include "../include/core/components/tag.hpp"
#include "../include/core/components/camera.hpp"
#include "../include/components/playerController.hpp"
#include "../include/core/components/boxCollider.hpp"
#include "../include/components/level.hpp"
#include "../include/components/parralax.hpp"
#include "../include/core/components/animator.hpp"

bool isDebug()
{
    return true;
}

void createCamera(std::shared_ptr<Coordinator> coordinator)
{
    Entity camera = coordinator->createEntity();

    coordinator->addComponent<Transform>(camera, Transform(1920/2, 1080/2, 1, 1));
    coordinator->addComponent<Camera>(camera);
    coordinator->addComponent<Tag>(camera, Tag("camera"));
}

void createLevel(std::shared_ptr<Coordinator> coordinator)
{
    Entity level = coordinator->createEntity();

    coordinator->addComponent<Tag>(level, Tag("level"));
    coordinator->addComponent<Level>(level);

    for (int i = 0; i < 36; i++) {
        Entity tile = coordinator->createEntity();
        coordinator->addComponent<Transform>(tile, Transform(i * 64, 950, 2, 2));
        coordinator->addComponent<SpriteRenderer>(tile, SpriteRenderer(TEXTURE_TYPE_RAIL, 32, 32, 3));
        coordinator->addComponent<Tag>(tile, Tag("rail"));
        coordinator->addComponent<Parralax>(tile, Parralax(400, i));
        auto &spriteRenderer = coordinator->_componentManager->getComponent<SpriteRenderer>(tile);
        spriteRenderer._color = sf::Color(220, 220, 220);
    }

    for (int i = 0; i < 4; i++) {
        Entity middleGround = coordinator->createEntity();
        coordinator->addComponent<Transform>(middleGround, Transform(i * 384 * 2, 720, 4, 4));
        coordinator->addComponent<SpriteRenderer>(middleGround, SpriteRenderer(TEXTURE_TYPE_MIDDLEGROUND, 192, 96, 2));
        coordinator->addComponent<Tag>(middleGround, Tag("middleGround"));
        coordinator->addComponent<Parralax>(middleGround, Parralax(200));
        auto &spriteRenderer = coordinator->_componentManager->getComponent<SpriteRenderer>(middleGround);
        spriteRenderer._color = sf::Color(140, 140, 140);
    }

    for (int i = 0; i < 4; i++) {
        Entity background = coordinator->createEntity();
        coordinator->addComponent<Transform>(background, Transform(i * 288 * 4, 600, 4, 4));
        coordinator->addComponent<SpriteRenderer>(background, SpriteRenderer(TEXTURE_TYPE_BACKGROUND, 288, 96, 1));
        coordinator->addComponent<Tag>(background, Tag("background"));
        coordinator->addComponent<Parralax>(background, Parralax(50));
        auto &spriteRenderer = coordinator->_componentManager->getComponent<SpriteRenderer>(background);
        spriteRenderer._color = sf::Color(80, 80, 80);
    }

    Entity moon = coordinator->createEntity();
    coordinator->addComponent<Transform>(moon, Transform(1920 /2, 1080/2, 1.5, 1.5));
    coordinator->addComponent<SpriteRenderer>(moon, SpriteRenderer(TEXTURE_TYPE_MOON, 256, 256, 0));
    coordinator->addComponent<Tag>(moon, Tag("moon"));
    coordinator->addComponent<Animator>(moon, Animator(Animation(2, 0.5)));
    auto &spriteRenderer = coordinator->_componentManager->getComponent<SpriteRenderer>(moon);
    spriteRenderer._color = sf::Color(220, 220, 220);

}

void createPlayer(std::shared_ptr<Coordinator> coordinator)
{
    Entity player = coordinator->createEntity();

    coordinator->addComponent<Transform>(player, Transform(300, 900, 2, 2));
    coordinator->addComponent<SpriteRenderer>(player, SpriteRenderer(TEXTURE_TYPE_JACK, 64, 64, 5));
    coordinator->addComponent<Tag>(player, Tag("player"));
    coordinator->addComponent<PlayerController>(player);
    auto &spriteRenderer = coordinator->_componentManager->getComponent<SpriteRenderer>(player);
    coordinator->addComponent<BoxCollider>(player, BoxCollider(32, 32, COLLISION_MODE_DYNAMIC));
    coordinator->addComponent<Animator>(player, Animator(Animation(2, 0.1)));
}

int main()
{
    srand(time(nullptr));
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    createCamera(coordinator);

    createLevel(coordinator);
    //put here your code to instantiate entities
    createPlayer(coordinator);

    if (serverRunning())
        return 0;

    int fps = 60;
    float timerFps = 0;
    while (coordinator->_window->isOpen()) {
        sf::Event event;
        while (coordinator->_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                coordinator->_window->close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            coordinator->_window->close();
            break;
        }
        coordinator->_window->clear();
        coordinator->update();
        if (isDebug()) {
            fps++;
            timerFps += coordinator->_deltaTime;
            if (timerFps >= 1) {
                std::cout << fps << std::endl;
                if (fps < 50)
                    std::cerr << "Low fps, Cause:" << coordinator->_highConsumingSystem << " with " << coordinator->_highConsumingTime * 1000 << "ms per frame" << std::endl;
                fps = 0;
                timerFps = 0;
                //coordinator->_networkManager->_clock.restart();
                //coordinator->_networkManager->sendPacket(coordinator->_networkManager->makePacket(CMD_PING, {}));
            }
        }
        coordinator->_window->display();
    }

    return 0;
}