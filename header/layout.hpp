#ifndef __LAYOUT_HPP__
#define __LAYOUT_HPP__

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "vec2.hpp"

// Forward declarations
class Element;
class Screen;
class Button;
class ClickEvent;

class Layout {
public:
    // Constructors
    Layout(vec2 startVec, vec2 endVec, int width, int height, bool isActive, std::string var);
    Layout();

    // Public Methods
    void draw(Screen& screen, int width, int height);
    void writeToFile(std::ostream& outFile);
    void printAttributes();
    ivec2 pointTranslator(ivec2 prePoint);
    std::shared_ptr<Layout> findLayout(std::string searchName, std::shared_ptr<Layout> currLayout);
    std::shared_ptr<Button> buttonSearch(ClickEvent e);

    // Public Attributes
    bool active;
    int isRootLayout;
    std::vector<std::shared_ptr<Element>> xmlItems;
    std::vector<std::shared_ptr<Layout>> layoutVec;
    std::vector<std::shared_ptr<Button>> buttonVec;
    std::string name;

private:
    // Private Attributes
    vec2 offsetVec;
};

#endif
