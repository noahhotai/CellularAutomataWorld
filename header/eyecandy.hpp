#ifndef __EYECANDY_HPP__
#define __EYECANDY_HPP__


#include <iostream>
#include <thread>
#include "vec2.hpp"
#include "vec3.hpp"
#include "screen.hpp"
#include "box.hpp"
#include "guifilegol.hpp"
#include "guifilewolfram.hpp"
#include "sound_player.hpp"


std::vector<std::string> globalVector1;
std::vector<std::string> globalVector2;

std::mutex globalMutex;
std::atomic<int> fileHasBeenChecked;

std::string trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace); // Skip leading spaces
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base(); // Skip trailing spaces
    return (start < end ? std::string(start, end) : ""); // Return trimmed string
}

void waitOnSound(){

    while (fileHasBeenChecked != 0){
        
    }
    
}


void getInput(){
    bool stopThreads = false;
    while (!stopThreads) {
        std::string newSongFileName;
        std::cout << "Enter a string (or 'exit' to quit): ";
        std::getline(std::cin, newSongFileName);
        newSongFileName = trim(newSongFileName);

        if (newSongFileName == "exit") {
            stopThreads = true;
            break;
        }

        std::string lOrR;
        std::cout << "Add to left or right sided queue (l/r): ";
        std::getline(std::cin, lOrR);
        lOrR = trim(lOrR);
        bool isLeft = true;
        while (1){
            if (lOrR == "l"){
                break;
            }
            else if (lOrR == "r"){
                isLeft = false;
                break;
            }
            else{
                std::cout << "Invalid input. Add to left or right sided queue (l/r): ";
                std::getline(std::cin, lOrR);
                lOrR = trim(lOrR);
            }
        }

        // Lock mutex before modifying the global variable
        {
            std::lock_guard<std::mutex> lock(globalMutex);
            if (isLeft == true){
                globalVector1.push_back(newSongFileName);
                std::cout << "song pushed\n";
                fileHasBeenChecked = 1;
            }
            else{
                globalVector2.push_back(newSongFileName);
                fileHasBeenChecked = 2;
            }
        }
        waitOnSound();
    }
}


void createInputThread(){
    std::thread inputThread(getInput);
    inputThread.detach();
}

#endif