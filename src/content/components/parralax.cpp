/*-----------------------------*
 * Pokenjos by Benjamin Bourge *
 *-----------------------------*/

#include "../../../include/components/parralax.hpp"


Parralax::Parralax()
{
    _speed = 0.0f;
    _id = -1;
}

Parralax::Parralax(float speed) : Parralax()
{
    _speed = speed;
}

Parralax::Parralax(float speed, int id) : Parralax()
{
    _speed = speed;
    _id = id;
}

Parralax::~Parralax()
{

}
