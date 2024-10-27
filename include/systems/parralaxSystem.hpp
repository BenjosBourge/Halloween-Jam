/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include "../core/system.hpp"

class ParralaxSystem : public System {
public:
    ParralaxSystem();
    ~ParralaxSystem();

    void update(float deltaTime) override;
    void addedEntity(Entity entity) override;
    void removedEntity(Entity entity) override;
};
