/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>

class Level {
public:
    Level();
    ~Level();

    float _speed;
    float _timerEnemy;
    float _timerToGenerateEnemy;

    float _timerMode;
    float _timerTransition;
};