/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>

class Enemy {
public:
    Enemy();
    Enemy(float speed);
    ~Enemy();

    float _speed;
    int _type;
    float _timeCreation;
    float _yCreation;
};