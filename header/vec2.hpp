#ifndef __VEC2_HPP__
#define __VEC2_HPP__
#include <cmath>
#include <stdexcept>  
#include "element.hpp"
#include <ostream> // Add this to enable << operator usage

//The code code and scope immediately following a template statement is templated
//  So, because we have the class scope below, all T's in the scope refer to this template statement

template <typename T>
class Tvec2
{
private:
    T components[2];
public:
    Tvec2() : components{0, 0}, x(components[0]), y(components[1])
    {

    }
    Tvec2(const Tvec2& cp) : Tvec2()
    {
        this->x = cp.x;
        this->y = cp.y;
    }
    Tvec2(T _x, T _y) : Tvec2()
    {
        this->x = _x;
        this->y = _y;
    }

    void writeToFile(std::ostream& outFile)  const{
        outFile << "        <ivec2>\n";
        outFile << "            <x>" << this->x << "</x>\n";
        outFile << "            <y>" << this->y << "</y>\n";
        outFile << "        </ivec2>\n";


    }

    Tvec2& operator=(const Tvec2& other)
    {   
        components[0] = other.x;
        components[1] = other.y;

        return *this;
    }
    Tvec2 operator+(const Tvec2& other) const {

        return Tvec2(this->x + other.x, this->y + other.y);
    }

    Tvec2 operator-(const Tvec2& other) const {
        return Tvec2(this->x - other.x, this->y - other.y);
    }

    Tvec2 operator*(T num) const {
        return Tvec2(this->x * num, this->y * num);
    }
    
    Tvec2 operator+=(const Tvec2& other){
        this->x = this->x + other.x;
        this->y = this->y + other.y;
        return *this;
    }

    Tvec2 operator-=(const Tvec2& other){
        this->x = this->x - other.x;
        this->y = this->y - other.y;
        return *this;
    }

    Tvec2 operator*=(const Tvec2& other){
        this->x = this->x * other.x;
        this->y = this->y * other.y;
        return *this;
    }

    bool operator ==(const Tvec2& other) const {
        return ((this->x == other.x) && (this->y == other.y));
    }

    T crossProduct(const Tvec2& other){
        return this->x * other.y - this->y * other.x;
    }


    T dot(Tvec2& other) const {
        return this->x * other.x + this->y * other.y;
    }
    
    T magnitude() const{ // always returns a float
        return std::sqrt((this->x * this->x) + (this->y * this->y));
    }

    Tvec2 unit_vector() const { //returns vector given if magnitude is 0
        float length = this->magnitude();
        if (length == 0) {
            return *this;
        }
        return Tvec2(this->x/length, this->y/length);
    }
    
    T& x, &y;
};

typedef Tvec2<float> vec2; 
typedef Tvec2<int> ivec2;

// template <>

// int Tvec2<int>::magnitude() const{ // always returns a float
//         return std::sqrt((this->x * this->x) + (this->y * this->y));
// }

#endif
