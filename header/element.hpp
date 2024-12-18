#ifndef __ELEMENT_HPP__
#define __ELEMENT_HPP__
#include <vector>
#include <memory>
#include "vec2.hpp"
#include "vec3.hpp"
#include <stdbool.h>
#include <iostream> // Add this to enable << operator usage

class Screen;
// class vec2;  // or struct vec2;
// Base class
class Element {
    public:
        virtual ~Element() = default;      // Virtual destructor
        virtual void draw(Screen& screen) const {}
        virtual void draw(Screen& screen, ivec3 startVec, ivec3 endVec, vec3 scalarVec) const {}
        virtual void printAttributes() const {}
        virtual void writeToFile(std::ostream& outFile) const {}
        virtual void rotate() {
            std::cout << "Base Element rotate called (no-op)" << std::endl;
        }
        virtual int checkInBounds(int x, int y) const {
            return 0;
        }
        ivec3 rgb;

};  



#endif
