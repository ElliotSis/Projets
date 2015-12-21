#include "Direction.h"

Direction operator - (const Direction& direction){
    return Direction(-direction.first, -direction.second);
}
