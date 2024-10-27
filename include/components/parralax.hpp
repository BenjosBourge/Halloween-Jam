/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>

class Parralax {
public:
    Parralax();
    Parralax(float speed);
    Parralax(float speed, int id);
    ~Parralax();

    float _speed;
    int _id;
};