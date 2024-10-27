/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../include/components/playerController.hpp"


PlayerController::PlayerController()
{
    _jumping = false;
    _timeBigJump = 0;
    _stoppedJumping = false;
    _speed = 0;
    _mode = 0;
    _timeNoControl = 0;
}

PlayerController::~PlayerController()
{

}
