/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../include/components/level.hpp"
#include <cstdlib>


Level::Level()
{
    _speed = 1.0f;
    _timerEnemy = 0.0f;
    _timerToGenerateEnemy = 1.0f;
    _timerMode = 15.f + rand() % 10;
    _timerTransition = 0.0f;
}

Level::~Level()
{

}
