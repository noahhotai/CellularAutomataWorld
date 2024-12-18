#ifndef __GUIFILE_WOLFRAM_HPP__
#define __GUIFILE_WOLFRAM_HPP__
#include <vector>
#include <memory>
#include "element.hpp"
#include "box.hpp"
#include "screen.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <memory>
#include "layout.hpp"
#include <stdbool.h>
#include <stdbool.h>
#include <random>

// Base class

class GUIFileWolfram {

private:
    int width;
    int height;
   
    std::vector<std::vector<int>> states;
    double boxWidth;
    double boxHeight;
    int wolfCode[8];

public:
    std::shared_ptr<Layout> rootLayoutPtr;
    GUIFileWolfram(int width, int height)
    : width(width), height(height) {

}   
    bool preserve;

    int getRandomNumber(int min, int max) const {
        static std::random_device rd;  // Seed only once
        static std::mt19937 gen(rd()); // Reuse the same generator
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    void render(Screen& screen) const {
        int rows = states.size();
        int cols = states[0].size();
        double boxWidth = static_cast<double>(width) / cols; // Use floating-point division
        double boxHeight = static_cast<double>(height) / rows; // Use floating-point division

        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                // Calculate coordinates using floating-point arithmetic
                double xStart = c * boxWidth;
                double yStart = r * boxHeight;
                double xEnd = (c + 1) * boxWidth;
                double yEnd = (r + 1) * boxHeight;

                ivec2 start(static_cast<int>(xStart), static_cast<int>(yStart));
                ivec2 end(static_cast<int>(xEnd), static_cast<int>(yEnd));

                // Determine color based on cell state
                ivec3 color = (states[r][c] == 1) ? ivec3(getRandomNumber(0, 200), getRandomNumber(0, 200), getRandomNumber(0, 200)) : ivec3(0, 0, 0);

                // Draw the box
                screen.drawBox(start, end, color);

                
            }
        }


        

    }

    void readInputWolfram() {

        std::string buffer;
        std::cout << "Enter Wolfram Code (Binary): ";
        std::cin >> buffer; 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int i = 0;
        int j = 0;
        while (i < buffer.size()) {
            if (buffer[i] == '0'){
                wolfCode[j] = 0;
                j+=1;
            }
            else if (buffer[i] == '1'){
                wolfCode[j] = 1;
                j+=1;
            }
            i++;
        }
        
        std::cout << "Enter start state: ";
        std::string startString;
        std::cin >> startString;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::vector<int> startState;
        i = 0;
        while (i < startString.size()) {
            if (startString[i] == '0'){
                startState.push_back(0);
            }
            else if (startString[i] == '1'){
                startState.push_back(1);
            }
            i++;
        }
        states.push_back(startState);
    }

    int calculateCellState(int left, int middle, int right){
        int index = 0;
        if (left) index+= 4;
        if (middle) index+= 2;
        if (right) index += 1;
        index = 7 - index;
        return wolfCode[index];
    }


    void iterateGeneration(){
        std::vector<int> newVector;

        if (states.size() == 0){
            return;
        }
        std::vector<int> lastVector = states[states.size()-1];
        for (int i = 0; i < lastVector.size(); i++){
            if (i == 0){
                newVector.push_back(calculateCellState(0, lastVector[i], lastVector[i+ 1]));
            }
            else if (i == 7){
                newVector.push_back(calculateCellState(lastVector[i - 1], lastVector[i], 0));
            }
            else{
                newVector.push_back(calculateCellState(lastVector[i - 1], lastVector[i], lastVector[i + 1]));
            }
        }

        if (preserve){
            states.push_back(newVector);
        }
        else{
            states.clear();
            states.push_back(newVector);
        }

    }
        


};  

#endif