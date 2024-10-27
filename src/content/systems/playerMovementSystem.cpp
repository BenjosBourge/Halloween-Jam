/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/playerMovementSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/playerController.hpp"
#include "../../../../include/core/components/transform.hpp"

PlayerMovementSystem::PlayerMovementSystem()
{
    _signature = getCoordinator()->getComponentSignature<Transform>();
    _signature |= getCoordinator()->getComponentSignature<PlayerController>();
}

PlayerMovementSystem::~PlayerMovementSystem()
{

}

void PlayerMovementSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();

    for (auto const& entity : _entitiesThisFrame) {
        auto &playerController = coordinator->getComponent<PlayerController>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (!playerController._jumping) {
                playerController._jumping = true;
                playerController._stoppedJumping = false;
                playerController._speed = -600;
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
        if (abs(playerController._speed) < 200)
            playerController._speed += 200 * deltaTime;
        playerController._speed += 2000 * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (playerController._speed < 1200)
                playerController._speed = 1200;
        }
        if (playerController._speed > 2500)
            playerController._speed = 2500;

        transform._y += playerController._speed * deltaTime;

        if (transform._y > 1080 - 150) {
            transform._y = 1080 - 150;
            playerController._speed = 0;
            playerController._jumping = false;
            playerController._stoppedJumping = false;
        } else if (transform._y < 100) {
            transform._y = 100;
        }
    }
}

void PlayerMovementSystem::addedEntity(Entity entity)
{

}

void PlayerMovementSystem::removedEntity(Entity entity)
{

}