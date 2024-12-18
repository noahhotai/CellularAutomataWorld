// ElementFactory.hpp
#ifndef __ELEMENTFACTORY_HPP__
#define __ELEMENTFACTORY_HPP__
#include <memory>
#include <string>
#include "element.hpp"
#include "box.hpp"
#include "line.hpp"
#include "point.hpp"
#include "layout.hpp"
#include "circle.hpp"


enum ElementType{
    BOX,
    LINE,
    POINT,
    TRIANGLE,
    LAYOUT,
    CIRCLE
};

class ElementFactory {
public:
    static std::shared_ptr<Element> createElement(const ElementType pointEnum, ivec2 coordinate, ivec3 rgb) {
        return std::make_shared<Point>(coordinate, rgb);
    }

    static std::shared_ptr<Element> createElement(const ElementType lineOrBox, ivec2 start, ivec2 end, ivec3 rgb) {

        if (lineOrBox == BOX){
            return std::make_shared<Box>(start, end, rgb);
        }
        else if (lineOrBox == LINE){
            return std::make_shared<Line>(start, end, rgb);
        }
        return std::make_shared<Line>(start, end, rgb);
    }

    // static std::shared_ptr<Element> createElement(const ElementType layoutEnum, vec2 start, vec2 end) {
    //     if (layoutEnum == LAYOUT) {
    //         std::cout << "element factory worked\n";
    //         return std::make_shared<Layout>(start, end);
    //     }
    //     std::cout << "element factory did not worked\n";
    //     return nullptr;
    // }

    static std::shared_ptr<Element> createElement(const ElementType triEnum, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 rgb) {
         return std::make_shared<Triangle>(point1, point2, point3, rgb);
    }
    static std::shared_ptr<Element> createElement(const ElementType circleEnum, ivec2 center, int radius, ivec3 rgb) {
        return std::make_shared<Circle>(center, radius, rgb);
    }

};

#endif
