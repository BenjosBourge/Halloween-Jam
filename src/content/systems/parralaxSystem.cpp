/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/parralaxSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/parralax.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/components/level.hpp"

ParralaxSystem::ParralaxSystem()
{
    _signature = getCoordinator()->getComponentSignature<Transform>();
    _signature |= getCoordinator()->getComponentSignature<Parralax>();
}

ParralaxSystem::~ParralaxSystem()
{

}

void ParralaxSystem::update(float deltaTime)
{
    std::shared_ptr<Coordinator> coordinator = getCoordinator();
    Entity level = coordinator->getEntityFromTag("level");
    auto &levelComponent = coordinator->getComponent<Level>(level);

    for (auto const& entity : _entitiesThisFrame) {
        auto &parralax = coordinator->getComponent<Parralax>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

        transform._x -= parralax._speed * deltaTime * levelComponent._speed;

        if (parralax._id >= 0) {
            if (transform._x < -64 * 3)
                transform._x += 1920 + 64 * 6;

                transform._y = 970 + levelComponent._timerTransition * 200;
        } else {
            if (transform._x < -192 * 3)
                transform._x += 1920 + 192 * 6;
        }
    }
}

void ParralaxSystem::addedEntity(Entity entity)
{

}

void ParralaxSystem::removedEntity(Entity entity)
{

}