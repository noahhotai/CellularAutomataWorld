#ifndef __BOX_HPP__
#define __BOX_HPP__
#include "vec2.hpp"
#include "vec3.hpp"
#include "element.hpp"
#include "screen.hpp"
#include <stdbool.h>

//The code code and scope immediately following a template statement is templated
//  So, because we have the class scope below, all T's in the scope refer to this template statement

class Box: public Element {
public:
    Box(ivec2 first, ivec2 second, ivec3 color, bool isIVec2Flag, bool isIVec3Flag)
        : start(first), end(second), isIVec2(isIVec2Flag), isIVec3(isIVec3Flag) {
            this->rgb = color;
        }

    Box(ivec2 first, ivec2 second, ivec3 color) : start(first), end(second) {
        this->rgb = color;
    }
    
    void draw(Screen& screen, ivec2 startVec, ivec2 endVec, vec2 scalarVec) const {
        screen.drawBox(start, end, rgb);
    }

    void draw(Screen& screen) const override {
        screen.drawBox(start, end, rgb);
    }

    void writeToFile(std::ostream& outFile) const override {
        outFile << "    <box>\n";
        start.writeToFile(outFile);
        end.writeToFile(outFile);
        rgb.writeToFile(outFile);

        outFile << "    </box>\n";

    }

    void printAttributes() const override {
        std::cout << "Box Attributes:" << std::endl;
        std::cout << "Start: (" << this->start.x << ", " << this->start.y << ")" << std::endl;
        std::cout << "End: (" << this->end.x << ", " << this->end.y << ")" << std::endl;
        std::cout << "Color (RGB): (" << rgb.x << ", " << rgb.y << ", " << rgb.z << ")" << std::endl;
        std::cout << "isIVec2: " << (isIVec2 ? "true" : "false") << std::endl;
        std::cout << "isIVec3: " << (isIVec3 ? "true" : "false") << std::endl;
    }
    void rotate() override{
        // std::cout << "box\n";
    }
    int checkInBounds(int x, int y) const {
        return (x >= start.x && x <= end.x && y >= start.y && y <= end.y);
    }


private:
    ivec2 start;
    ivec2 end;
    bool isIVec2;
    bool isIVec3;
};




#endif
