/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../../include/systems/levelSystem.hpp"
#include "../../../../include/core/coordinator.hpp"
#include "../../../../include/components/playerController.hpp"
#include "../../../../include/core/components/transform.hpp"
#include "../../../../include/components/level.hpp"

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

    for (auto const& entity : _entitiesThisFrame) {
        auto &playerController = coordinator->getComponent<LevelSystem>(entity);
        auto &transform = coordinator->getComponent<Transform>(entity);

    }
}

void LevelSystem::addedEntity(Entity entity)
{

}

void LevelSystem::removedEntity(Entity entity)
{

}