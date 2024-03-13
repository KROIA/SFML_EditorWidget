#include "utilities/VectorOperations.h"
#include "utilities/RandomEngine.h"

#define _USE_MATH_DEFINES
#include <math.h>
#define M_2PI (2 * M_PI)

namespace QSFML
{
namespace VectorMath
{
    float getLength(const sf::Vector2f &vec)
    {
        return sqrt( vec.x * vec.x + vec.y * vec.y);
    }
    double getLength(const Vector2d &vec)
    {
        return sqrt( vec.x * vec.x + vec.y * vec.y);
    }
    float getSquareLength(const sf::Vector2f &vec)
    {
        return vec.x * vec.x + vec.y * vec.y;
    }
    double getSquareLength(const Vector2d& vec)
    {
        return vec.x * vec.x + vec.y * vec.y;
    }
    sf::Vector2f getRotatedUnitVector(float rad)
    {
        return sf::Vector2f(cos(rad), sin(rad));
    }
    Vector2d getRotatedUnitVector(double rad)
    {
        return Vector2d(cos(rad), sin(rad));
    }
    sf::Vector2f getRotated(const sf::Vector2f &vec, float rad)
    {
        float angle = getAngle(vec);
        angle += rad;
        return sf::Vector2f(cos(angle), sin(angle)) * getLength(vec);
    }
    Vector2d getRotated(const Vector2d& vec, double rad)
    {
        double angle = getAngle(vec);
        angle += rad;
        return Vector2d(cos(angle), sin(angle)) * getLength(vec);
    }
    sf::Vector2f getRotated(const sf::Vector2f &vec, const sf::Vector2f &origin, float rad)
    {
        return getRotated(vec - origin, rad) + origin;
    }
    Vector2d getRotated(const Vector2d& vec, const Vector2d& origin, double rad)
    {
        return getRotated(vec - origin, rad) + origin;
    }
    float getAngle(const sf::Vector2f &vec)
    {
#ifdef QSFML_OPTIMIZED
        float sqrL = vec.x * vec.x + vec.y * vec.y;

        if (sqrL == 0)
            return 0;

        float angle = atan2(vec.y, vec.x);
        angle = fmod(angle + M_PI, 2 * M_PI);
        
        return (angle < 0) ? angle + 2 * M_PI - M_PI : angle - M_PI;
#else

        float sqrL = getSquareLength(vec);
        if(sqrL <= 0)
            return 0;
        float angle;
        sqrL = sqrt(sqrL);

        if (vec.y <= 0) {
            angle = -acos(vec.x / sqrL);
        }
        else {
            angle = acos(vec.x / sqrL);
        }
        return getNormalzedAngle(angle);
#endif
        return 0;
    }
    double getAngle(const Vector2d& vec)
    {
#ifdef QSFML_OPTIMIZED
        double sqrL = vec.x * vec.x + vec.y * vec.y;

        if (sqrL == 0)
            return 0;

        double angle = atan2(vec.y, vec.x);
        angle = fmod(angle + M_PI, 2 * M_PI);

        return (angle < 0) ? angle + 2 * M_PI - M_PI : angle - M_PI;
#else

        double sqrL = getSquareLength(vec);
        if (sqrL <= 0)
            return 0;
        double angle;
        sqrL = sqrt(sqrL);

        if (vec.y <= 0) {
            angle = -acos(vec.x / sqrL);
        }
        else {
            angle = acos(vec.x / sqrL);
        }
        return getNormalzedAngle(angle);
#endif
        return 0;
    }
    float getAngle(const sf::Vector2f &vec1, const sf::Vector2f &vec2)
    {
        float dotProduct = vec1.x * vec2.x + vec1.y * vec2.y;
        float determinant = vec1.x * vec2.y - vec1.y * vec2.x;
        float length = getLength(vec1) * getLength(vec2);

        float angle = 0.0f;

        if (determinant >= 0) {
            angle = acos(dotProduct/ length);
        }
        else {
            angle = 2 * M_PI - acos(dotProduct/ length);
        }

        return getNormalzedAngle(angle);
    }
    double getAngle(const Vector2d& vec1, const Vector2d& vec2)
    {
        double dotProduct = vec1.x * vec2.x + vec1.y * vec2.y;
        double determinant = vec1.x * vec2.y - vec1.y * vec2.x;
        double length = getLength(vec1) * getLength(vec2);

        double angle = 0.0f;

        if (determinant >= 0) {
            angle = acos(dotProduct / length);
        }
        else {
            angle = 2 * M_PI - acos(dotProduct / length);
        }

        return getNormalzedAngle(angle);
    }
    float dotProduct(const sf::Vector2f &vec1, const sf::Vector2f &vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }
    double dotProduct(const Vector2d& vec1, const Vector2d& vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }
    float crossProduct(const sf::Vector2f &vec1, const sf::Vector2f &vec2)
    {
        return vec1.x * vec2.y - vec1.y * vec2.x;
    }
    double crossProduct(const Vector2d& vec1, const Vector2d& vec2)
    {
        return vec1.x * vec2.y - vec1.y * vec2.x;
    }
    const sf::Vector2f &getUnitVector()
    {
        static const sf::Vector2f v(1,0);
        return v;
    }
    const Vector2d& getUnitVectorD()
    {
        static const Vector2d v(1, 0);
        return v;
    }
    sf::Vector2f getNormalized(const sf::Vector2f &vec)
    {
        float l = vec.x * vec.x + vec.y * vec.y;
        if(l <= 0)
            return vec;
        return(vec / (float)sqrt(l));
    }
    Vector2d getNormalized(const Vector2d& vec)
    {
        double l = vec.x * vec.x + vec.y * vec.y;
        if (l <= 0)
            return vec;
        return(vec / sqrt(l));
    }

    float getNormalzedAngle(float angle)
    {
#ifdef QSFML_OPTIMIZED
        angle = fmod(angle + M_PI, 2 * M_PI);
        return (angle < 0) ? angle + 2 * M_PI - M_PI : angle - M_PI;
#else
        angle = fmod(angle + M_PI, 2 * M_PI);
        if (angle < 0)
            angle += 2 * M_PI;
        return angle - M_PI;
#endif
    }
    double getNormalzedAngle(double angle)
    {
#ifdef QSFML_OPTIMIZED
        angle = fmod(angle + M_PI, 2 * M_PI);
        return (angle < 0) ? angle + 2 * M_PI - M_PI : angle - M_PI;
#else
        angle = fmod(angle + M_PI, 2 * M_PI);
        if (angle < 0)
            angle += 2 * M_PI;
        return angle - M_PI;
#endif
    }
    bool isAngleInRange(float angle, float minAngle, float maxAngle)
    {
        // Normalize angles to be in the range [0, 2*pi)
        angle = fmod(angle, M_2PI);
        if (angle < 0)
            angle += M_2PI;

        minAngle = fmod(minAngle, M_2PI);
        if (minAngle < 0)
            minAngle += M_2PI;

        maxAngle = fmod(maxAngle, M_2PI);
        if (maxAngle < 0)
            maxAngle += M_2PI;

        // Case where the angle wraps around
        if (minAngle > maxAngle) {
            return (angle >= minAngle || angle <= maxAngle);
        }

        // Case where the angle does not wrap around
        return (angle >= minAngle && angle <= maxAngle);
    }
    bool isAngleInRange(double angle, double minAngle, double maxAngle)
    {
        // Normalize angles to be in the range [0, 2*pi)
        angle = fmod(angle, M_2PI);
        if (angle < 0)
            angle += M_2PI;

        minAngle = fmod(minAngle, M_2PI);
        if (minAngle < 0)
            minAngle += M_2PI;

        maxAngle = fmod(maxAngle, M_2PI);
        if (maxAngle < 0)
            maxAngle += M_2PI;

        // Case where the angle wraps around
        if (minAngle > maxAngle) {
            return (angle >= minAngle || angle <= maxAngle);
        }

        // Case where the angle does not wrap around
        return (angle >= minAngle && angle <= maxAngle);
    }
}
}
