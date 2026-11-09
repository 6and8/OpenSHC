#include "../EntityState.func.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402DA0
        int EntityState::computeVelocity(int param_2, double angleDegrees, int distance, int heightDifference)
        {
            double const angle = angleDegrees * 3.1415926535 / 180.0;
            double const range = distance * 2;
            double const cosAngle = cos(angle);
            return (int)sqrt((9.812 * range * range / (cosAngle * cosAngle)) / (tan(angle) * range - heightDifference / 4));
        }

    }
}
}
