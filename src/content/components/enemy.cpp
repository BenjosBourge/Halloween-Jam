/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../include/components/enemy.hpp"


Enemy::Enemy() {
    _speed = 0;
    _type = 0;
    _timeCreation = 0;
    _yCreation = 0;
}

Enemy::Enemy(float speed) {
    _speed = speed;
    _type = 0;
    _timeCreation = 0;
    _yCreation = 0;
}

Enemy::~Enemy() {

}
