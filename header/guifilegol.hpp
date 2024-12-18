#ifndef __GUIFILE_HPP__
#define __GUIFILE_HPP__
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
#include <stdbool.h>
#include <stdbool.h>
#include <random>

// Base class

class GUIFileGOL{

private:
    
    std::ifstream file;
    std::ofstream outFile;
    std::vector<std::string> stringItems;
    int width;
    int height;

public:
    GUIFileGOL(int width, int height)
    : width(width), height(height){
}

    int getRandomNumber(int min, int max) const {
        static std::random_device rd;  // Seed only once
        static std::mt19937 gen(rd()); // Reuse the same generator
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    void renderGOL(Screen& screen) const {
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
                ivec3 color = (intArrayGOL[r][c] == 1) ? ivec3(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255)) : ivec3(0, 0, 0);

                // Draw the box
                screen.drawBox(start, end, color);
            }
        }
    }

    void readFileGOL(const std::string& filename) {

        //open file
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        // read file into one string
        std::string line;
        std::string data;
        cols = 0;
        bool countCols = 1;

        while (std::getline(file, line)) {
            for (char c : line) {
                if (!std::isspace(static_cast<unsigned char>(c))) {
                    data += c;
                    if (countCols){
                        cols++;
                    }
                }
            }
            if (countCols){
                cols = data.size();
                countCols = 0;
            }

        }

        std::string data2;
        for(auto c: data){
            if (!std::isspace(static_cast<unsigned char>(c))){
                data2 += c;
            }
        }

        

        //take items from string and add them to vector
        int dataIndex = 0;
        int arrayIndex = 0;
        std::vector<int> currRow;
        rows = 0;
        while(dataIndex < data2.size()){
            arrayIndex = dataIndex % cols;

            if (data2[dataIndex] == '1'){
                currRow.push_back(1);
            }
            else{
                currRow.push_back(0);
            }

            if (arrayIndex == cols - 1){
                rows++;
                intArrayGOL.push_back(currRow);
                currRow.clear();
            }
            dataIndex++;
        }

        boxWidth = static_cast<double>(width) / cols; // Use floating-point division
        boxHeight = static_cast<double>(height) / rows; // Use floating-point division
        file.close();
    }

    int countLiveNeighbors(int row, int col){
        int count = 0;
        if ((row -1) >= 0 && (row-1) < rows && (col-1) >= 0 && (col -1) < cols){
            if (intArrayGOL[row-1][col -1] == 1){
                count++;
            }
        }

        if ((row -1) >= 0 && (row-1) < rows && (col) >= 0 && (col) < cols){
            if (intArrayGOL[row-1][col] == 1){
                count++;
            }
        }

        if ((row -1) >= 0 && (row-1) < rows && (col+1) >= 0 && (col+1) < cols){
            if (intArrayGOL[row-1][col +1] == 1){
                count++;
            }
        }

        if ((row) >= 0 && (row) < rows && (col-1) >= 0 && (col -1) < cols){
            if (intArrayGOL[row][col -1] == 1){
                count++;
            }
        }

        if ((row) >= 0 && (row) < rows && (col+1) >= 0 && (col +1) < cols){
            if (intArrayGOL[row][col +1] == 1){
                count++;
            }
        }

        if ((row+1) >= 0 && (row+1) < rows && (col-1) >= 0 && (col -1) < cols){
            if (intArrayGOL[row+1][col -1] == 1){
                count++;
            }
        }

        if ((row+ 1) >= 0 && (row + 1) < rows && (col) >= 0 && (col) < cols){
            if (intArrayGOL[row+ 1][col] == 1){
                count++;
            }
        }

        if ((row + 1) >= 0 && (row + 1) < rows && (col+1) >= 0 && (col +1) < cols){
            if (intArrayGOL[row + 1][col +1] == 1){
                count++;
            }
        }
        return count;
    }


    void iterateGenerationGOL(){
        std::vector<std::vector<int>> newIntArrayGOL;
        std::vector<int> helperVector;
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < cols; c++){
                int neighbors = countLiveNeighbors(r, c);
                if (intArrayGOL[r][c] == 1){
                    if (neighbors > 1 && neighbors < 4){
                        helperVector.push_back(1);
                    }
                    else{
                        helperVector.push_back(0);
                    }
                }
                else{
                    if (neighbors != 3){
                        helperVector.push_back(0);
                    }
                    else{
                        helperVector.push_back(1);
                    }
                }
            }
            newIntArrayGOL.push_back(helperVector);
            helperVector.clear();
        }
        intArrayGOL = newIntArrayGOL;
    }
        
    void printGOL(){
        // system("clear");
        std::cout << "\n";
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < cols; c++){
                std::cout << intArrayGOL[r][c];
            }
            std::cout << "\n";
        }

    }

    std::vector<std::vector<int>> intArrayGOL;
    int rows;
    int cols;
    double boxWidth;
    double boxHeight;

};  

#endif