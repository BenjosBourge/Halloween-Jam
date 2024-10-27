/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/levelSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/playerController.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/components/level.hpp"
#include "../../../../include/components/enemy.hpp"
#include "../../../../include/core/components/boxCollider.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"
#include "../../../../include/core/myMath.hpp"
#include "../../../../include/core/components/animator.hpp"
#include <cmath>

LevelSystem::LevelSystem()
{
    _signature = getCoordinator()->getComponentSignature<Level>();
}

LevelSystem::~LevelSystem()
{

}

void LevelSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity player = coordinator->getEntityFromTag("player");
    auto &playerController = coordinator->getComponent<PlayerController>(player);

    for (auto const& entity : _entitiesThisFrame) {
        auto &level = coordinator->getComponent<Level>(entity);

        if (level._speed > 2)
            level._speed += 0.02 * deltaTime;
        else
            level._speed += 0.04 * deltaTime;

        level._timerEnemy += deltaTime;
        level._timerMode -= deltaTime;
        if (level._timerMode < 0) {
            level._timerMode = 20 + rand() % 20;
            playerController._mode = 1 - playerController._mode;

            if (playerController._mode == 1) {
                playerController._speed = -2000;
                playerController._timeNoControl = 1.f;
            }
        }

        if (playerController._mode == 1) {
            level._timerTransition += deltaTime;
            if (level._timerTransition > 1) {
                level._timerTransition = 1;
            }
        } else {
            level._timerTransition -= deltaTime;
            if (level._timerTransition < 0) {
                level._timerTransition = 0;
            }
        }

        if (level._timerEnemy >= level._timerToGenerateEnemy) {
            level._timerEnemy = 0;
            level._timerToGenerateEnemy = 1 + rand() % 3 - sqrt(level._speed);
            if (level._timerToGenerateEnemy < 0.5)
                level._timerToGenerateEnemy = 0.5;
            if (level._speed < 2 && level._timerToGenerateEnemy < 1)
                level._timerToGenerateEnemy = 1;

            int type = 0;
            int r = rand() % 100;
            if (r > 80 && level._speed > 1.5)
                type = 1;
            else if (r > 60 && level._speed > 2)
                type = 2;

            if (playerController._mode == 1) {
                type = 3;
                if (r > 80)
                    type = 4;
                else if (r > 70)
                    type = 5;
            }

            Entity enemy = coordinator->createEntity();
            coordinator->addComponent<Transform>(enemy, Transform(2000, 930, 2, 2));
            coordinator->addComponent<Enemy>(enemy, Enemy(400));
            coordinator->addComponent<BoxCollider>(enemy, BoxCollider(64, 64));
            coordinator->addComponent<SpriteRenderer>(enemy, SpriteRenderer(TEXTURE_TYPE_ENEMIES, 64, 64, 5));
            auto &spriteRenderer = coordinator->_componentManager->getComponent<SpriteRenderer>(enemy);
            spriteRenderer._color = sf::Color(255, 0, 0);
            auto &enemyComponent = coordinator->getComponent<Enemy>(enemy);
            enemyComponent._type = type;
            coordinator->addComponent<Animator>(enemy, Animator(Animation(2, 0.5)));
            auto &animator = coordinator->getComponent<Animator>(enemy);
            animator._verticalOffset = 1;

            if (type == 1) {
                auto &transform = coordinator->getComponent<Transform>(enemy);
                transform._y = 930 - 90 * (rand() % 3 + 1);
                animator._verticalOffset = 2;
            }
            if (type == 2) {
                enemyComponent._timeCreation = rand() % 100;
                animator._verticalOffset = 0;
            }
            if (type == 3) {
                auto &transform = coordinator->getComponent<Transform>(enemy);
                transform._y = 1000 - 90 * (rand() % 11);
                animator._verticalOffset = 2;
            }
            if (type == 4) {
                int y = 930 - 90 * (rand() % 9);
                auto &transform = coordinator->getComponent<Transform>(enemy);
                transform._y = y;
                animator._verticalOffset = 3;

                Entity enemy2 = coordinator->createEntity();
                coordinator->addComponent<Transform>(enemy2, Transform(2000, 930, 2, 2));
                coordinator->addComponent<Enemy>(enemy2, Enemy(400));
                coordinator->addComponent<BoxCollider>(enemy2, BoxCollider(64, 64));
                coordinator->addComponent<SpriteRenderer>(enemy2, SpriteRenderer(TEXTURE_TYPE_ENEMIES, 64, 64, 5));
                coordinator->addComponent<Animator>(enemy2, Animator(Animation(2, 0.5)));
                auto &spriteRenderer2 = coordinator->_componentManager->getComponent<SpriteRenderer>(enemy2);
                spriteRenderer2._color = sf::Color(255, 0, 0);
                auto &enemyComponent2 = coordinator->getComponent<Enemy>(enemy2);
                enemyComponent2._type = type;
                auto &transform2 = coordinator->getComponent<Transform>(enemy2);
                transform2._y = y - 90;
                auto &animator2 = coordinator->getComponent<Animator>(enemy2);
                animator2._verticalOffset = 3;

                Entity enemy3 = coordinator->createEntity();
                coordinator->addComponent<Transform>(enemy3, Transform(2000, 930, 2, 2));
                coordinator->addComponent<Enemy>(enemy3, Enemy(400));
                coordinator->addComponent<BoxCollider>(enemy3, BoxCollider(64, 64));
                coordinator->addComponent<SpriteRenderer>(enemy3, SpriteRenderer(TEXTURE_TYPE_ENEMIES, 64, 64, 5));
                coordinator->addComponent<Animator>(enemy3, Animator(Animation(2, 0.5)));
                auto &spriteRenderer3 = coordinator->_componentManager->getComponent<SpriteRenderer>(enemy3);
                spriteRenderer3._color = sf::Color(255, 0, 0);
                auto &enemyComponent3 = coordinator->getComponent<Enemy>(enemy3);
                enemyComponent3._type = type;
                auto &transform3 = coordinator->getComponent<Transform>(enemy3);
                transform3._y = y + 90;
                auto &animator3 = coordinator->getComponent<Animator>(enemy3);
                animator3._verticalOffset = 3;
            }
            if (type == 5) {
                spriteRenderer._color = sf::Color(255, 0, 0);
                auto &transform = coordinator->getComponent<Transform>(enemy);
                enemyComponent._timeCreation = rand() % 100;
                enemyComponent._yCreation = 930 - 90 * (rand() % 9);
                animator._verticalOffset = 0;
            }
        }
    }
}

void LevelSystem::addedEntity(Entity entity)
{

}

void LevelSystem::removedEntity(Entity entity)
{

}