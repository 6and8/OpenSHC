#include "../EntityState.func.hpp"

#include "float.h"
#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402C50
        int EntityState::math_atan_1(int entityType, double velocity, int distance, int heightDifference)
        {
            double const velocitySquared = velocity * velocity;
            distance *= 4;
            heightDifference /= 2;
            double const range = distance;
            double const rangeSquared = range * range;
            double const ratio = velocitySquared / (range * 9.812);
            double const root = sqrt(velocitySquared * velocitySquared / (96.275344 * rangeSquared)
                - 2.0 * velocitySquared * heightDifference / (9.812 * rangeSquared) - 1.0);
            int lowAngle;
            double tangent = ratio - root;
            if (!(tangent == HUGE_VAL || _isnan(tangent))) {
                lowAngle = (int)(atan(tangent) * 180.0 / 3.1415926535 + 0.4999f);
            } else {
                lowAngle = 1000;
            }
            int highAngle;
            tangent = root + ratio;
            if (tangent == HUGE_VAL || _isnan(tangent)) {
                highAngle = 1000;
            } else {
                highAngle = (int)(atan(tangent) * 180.0 / 3.1415926535 + 0.4999f);
            }
            int angle;
            if (lowAngle < highAngle) {
                angle = lowAngle;
            } else {
                angle = highAngle;
            }
            if (angle < -90) {
                if (lowAngle > highAngle) {
                    angle = lowAngle;
                } else {
                    angle = highAngle;
                }
                if (angle < -90) {
                    return 45;
                }
            }
            if (angle > 90) {
                return 45;
            }
            return angle;
        }

    }
}
}
