/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <map>

class PlayerController {
public:
    PlayerController();
    ~PlayerController();

    bool _jumping;
    float _timeBigJump;
    bool _stoppedJumping;

    float _speed;
    float _timeNoControl;

    int _mode;
};