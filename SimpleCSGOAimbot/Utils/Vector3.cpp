#include "Vector3.h"

float Vector3::magnitude(Vector3 target) {
	return sqrtf(pow(target.x - this->x, 2) + pow(target.y - this->y, 2) + pow(target.z - this->z, 2));
}

float Vector3::yawAngle(Vector3 target) {
	return atan2f(target.y - this->y, target.x - this->x) * (180 / M_PI);
}

float Vector3::pitchAngle(Vector3 target) {
    float magnitude = this->magnitude(target);
    if (magnitude == 0) {
        // Handle the case when the magnitude is zero to avoid division by zero
        return 0.0f;
    }
    /*
    * For Debug
    float temp = fabsf((fabsf(target.z) - fabsf(this->z)));

    float temp1 = temp / magnitude;
    float tempp = asin(temp1) * (180.0f / M_PI);
    */

    return asin(fabsf((fabsf(target.z) - fabsf(this->z))) / magnitude) * (180/ M_PI);
}
