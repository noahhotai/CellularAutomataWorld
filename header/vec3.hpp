#ifndef __VEC3_HPP__
#define __VEC3_HPP__
#include <stdexcept>  
#include <cmath>
#include "element.hpp"
#include <ostream> // Add this to enable << operator usage

//The code code and scope immediately following a template statement is templated
//  So, because we have the class scope below, all T's in the scope refer to this template statement
template <typename T>
class Tvec3
{
private:
    T components[3];
public:

    Tvec3() : components{0, 0, 0}, x(components[0]), y(components[1]), z(components[2])
    {

    }
    Tvec3(const Tvec3& cp) : Tvec3()
    {
        this->x = cp.x;
        this->y = cp.y;
        this->z = cp.z;
    }
    
    Tvec3(T _x, T _y, T _z) : Tvec3()
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
    }

    void writeToFile(std::ostream& outFile) const{
        outFile << "        <ivec2>\n";
        outFile << "            <x>" << this->x << "</x>\n";
        outFile << "            <y>" << this->y << "</y>\n";
        outFile << "            <z>" << this->z << "</z>\n";
        outFile << "        </ivec2>\n";

    }

    Tvec3& operator=(const Tvec3& other) 
    {   

            components[0] = other.x;
            components[1] = other.y;
            components[2] = other.z;

           
        return *this;
    }

    Tvec3 operator+(const Tvec3& other) const {
        return Tvec3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Tvec3 operator-(const Tvec3& other) const {
        return Tvec3(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    Tvec3 operator+=(const Tvec3& other) {
        this->x = this->x + other.x;
        this->y = this->y + other.y;
        this->z = this->z + other.z;
        return *this;
    }

    Tvec3 operator-=(const Tvec3& other) {
        this->x = this->x - other.x;
        this->y = this->y - other.y;
        this->z = this->z - other.z;
        return *this;
    }

    Tvec3 operator*=(const Tvec3& other) {
        this->x = this->x * other.x;
        this->y = this->y * other.y;
        this->z = this->z * other.z;
        return *this;
    }

    bool operator ==(const Tvec3& other) const {
        return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
    }

    T magnitude() const{ //
        return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
    }

    Tvec3 unit_vector() const { //returns vector given if magnitude is 0
        float length = this->magnitude();
        if (length == 0) {
            return *this;
        }
        return Tvec3(this->x/length, this->y/length, this->z/length);
    }

    T dot(Tvec3& other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }
    
    Tvec3 cross(Tvec3& other) const{
        return Tvec3(
            this->y * other.z - this->z * other.y, // Cx
            this->z * other.x - this->x * other.z, // Cy
            this->x * other.y - this->y * other.x  // Cz
        );
    }

    T& x, &y, &z;
};

typedef Tvec3<float> vec3; 
typedef Tvec3<int> ivec3;

// template <>
// int Tvec3<int>::magnitude() const{ // always returns a float
//     return std::sqrt((this->x * this->x) + (this->y * this->y) + ((this->z * this->z)));
// }

#endif
