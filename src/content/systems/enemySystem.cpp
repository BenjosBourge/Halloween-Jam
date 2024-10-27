/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/enemySystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/enemy.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/components/level.hpp"
#include "../../../../include/core/myMath.hpp"
#include "../../../../include/components/playerController.hpp"

EnemySystem::EnemySystem()
{
    _signature = getCoordinator()->getComponentSignature<Enemy>();
    _signature |= getCoordinator()->getComponentSignature<Transform>();
}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity level = coordinator->getEntityFromTag("level");
    auto &levelComponent = coordinator->getComponent<Level>(level);
    Entity player = coordinator->getEntityFromTag("player");
    auto &playerController = coordinator->getComponent<PlayerController>(player);

    for (auto const& entity : _entitiesThisFrame) {
        auto &enemy = coordinator->getComponent<Enemy>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

        enemy._timeCreation += deltaTime;
        transform._x -= enemy._speed * deltaTime * levelComponent._speed;

        if (transform._x < -64) {
            coordinator->killEntity(entity);
        }

        if (enemy._type == 2 && playerController._mode == 0) {
            transform._y = 930 + 200 * my_sin(enemy._timeCreation * 5) - 200;
        }
        if (enemy._type == 5 && playerController._mode == 1) {
            transform._y = enemy._yCreation + 200 * my_sin(enemy._timeCreation * 5) - 200;
        }

        if (enemy._type >= 0 && enemy._type <= 2) {
            if (playerController._mode == 1) {
                transform._y += 200 * deltaTime;
                if (transform._y > 1180) {
                    coordinator->killEntity(entity);
                }
            }
        }
        if (enemy._type >= 3 && enemy._type <= 5) {
            if (playerController._mode == 0) {
                transform._y -= 400 * deltaTime;
                if (transform._y < -64) {
                    coordinator->killEntity(entity);
                }
            }
        }
    }
}

void EnemySystem::addedEntity(Entity entity)
{

}

void EnemySystem::removedEntity(Entity entity)
{

}