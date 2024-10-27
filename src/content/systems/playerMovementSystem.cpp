/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/playerMovementSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/playerController.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/components/level.hpp"
#include "../../../../include/core/components/spriteRenderer.hpp"
#include "../../../../include/core/myMath.hpp"
#include "../../../../include/core/components/boxCollider.hpp"
#include "../../../../include/components/enemy.hpp"
#include "../../../../include/core/components/animator.hpp"

PlayerMovementSystem::PlayerMovementSystem()
{
    _signature = getCoordinator()->getComponentSignature<Transform>();
    _signature |= getCoordinator()->getComponentSignature<PlayerController>();
    _signature |= getCoordinator()->getComponentSignature<SpriteRenderer>();
    _signature |= getCoordinator()->getComponentSignature<BoxCollider>();
    _signature |= getCoordinator()->getComponentSignature<Animator>();
}

PlayerMovementSystem::~PlayerMovementSystem()
{

}

void PlayerMovementSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity level = coordinator->getEntityFromTag("level");
    auto &levelComponent = coordinator->getComponent<Level>(level);

    for (auto const& entity : _entitiesThisFrame) {
        auto &playerController = coordinator->getComponent<PlayerController>(entity);
        auto &spriteRenderer = coordinator->getComponent<SpriteRenderer>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);
        auto &boxCollider = coordinator->getComponent<BoxCollider>(entity);
        auto &animator = coordinator->getComponent<Animator>(entity);

        animator._verticalOffset = playerController._mode;

        if (boxCollider._entitiesCollided.size() > 0) {
            playerController._speed = 0;
            playerController._jumping = false;
            playerController._stoppedJumping = false;
            playerController._timeNoControl = 0.f;
            playerController._mode = 0;
            transform._y = 930;

            std::vector<Entity> enemies = coordinator->getAllEntitiesWithComponent<Enemy>();
            for (auto const& enemy : enemies) {
                coordinator->killEntity(enemy);
            }
            levelComponent._speed = 1;
            levelComponent._timerMode = 20 + rand() % 20;
        }

        if (levelComponent._timerMode < 2.5) {
            int c = 255 - my_sin(levelComponent._timerMode * 3.1415 * 10) * 100;
            spriteRenderer._color = sf::Color(c, c, c);
        } else
            spriteRenderer._color = sf::Color(255, 255, 255);

        if (playerController._mode == 0) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (!playerController._jumping) {
                    playerController._jumping = true;
                    playerController._stoppedJumping = false;
                    playerController._speed = -1000;
                    playerController._timeBigJump = 0;
                }
            } else {
                if (playerController._jumping && !playerController._stoppedJumping) {
                    playerController._stoppedJumping = true;
                    playerController._jumping = true;
                }
            }

            if (playerController._jumping && !playerController._stoppedJumping) {
                playerController._speed -= 2000 * deltaTime;

                playerController._timeBigJump += deltaTime;
                if (playerController._timeBigJump > 0.2) {
                    playerController._stoppedJumping = true;
                }
            }

            // position
            if (abs(playerController._speed) < 500)
                playerController._speed += 1000 * deltaTime;
            if (playerController._speed < 0)
                playerController._speed += 1500 * deltaTime;
            playerController._speed += 2000 * deltaTime;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (playerController._speed < 1200)
                    playerController._speed = 1200;
            }
            if (playerController._speed > 2500)
                playerController._speed = 2500;

            transform._y += playerController._speed * deltaTime;

            if (transform._y > 930) {
                transform._y = 930;
                playerController._speed = 0;
                playerController._jumping = false;
                playerController._stoppedJumping = false;
            } else if (transform._y < 100) {
                transform._y = 100;
            }
        } else {
            playerController._timeNoControl -= deltaTime;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerController._timeNoControl <= 0) {
                playerController._speed -= 2000 * deltaTime;
            } else {
                if (abs(playerController._speed) < 500)
                    playerController._speed += 500 * deltaTime;
                if (playerController._speed < 0)
                    playerController._speed += 1500 * deltaTime;
                playerController._speed += 1500 * deltaTime;
            }

            transform._y += playerController._speed * deltaTime;

            if (transform._y > 930) {
                transform._y = 930;
            } else if (transform._y < 100) {
                transform._y = 100;
            }
        }
    }
}

void PlayerMovementSystem::addedEntity(Entity entity)
{

}

void PlayerMovementSystem::removedEntity(Entity entity)
{

}