#include "../header/vec2.hpp"
#include "../header/vec3.hpp"
#include "../header/box.hpp"
#include "../header/guifilegol.hpp"
#include "../header/guifilewolfram.hpp"
#include "../header/screen.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <string>

// Input helper function
void inputHelper(const std::string& s, char& c) {
    for (auto i : s) {
        if (!std::isspace(static_cast<unsigned char>(i))) {
            c = i;
            return;
        }
    }
}

// Input helper for integers
int inputHelperInt(const std::string& s) {
    std::string trimmed;
    for (auto i : s) {
        if (!std::isspace(static_cast<unsigned char>(i))) {
            trimmed += i;
        }
    }
    return std::stoi(trimmed);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    unsigned int width = 800;
    unsigned int height = 800;

    SDL_Window* window = SDL_CreateWindow("SDL Screen Example",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);

    Screen screen(width, height);

    // Input handling using inputHelper and getline
    std::string inputBuffer;
    char letter;
    std::cout << "Welcome to Cellular Automata World!\nWould you like to do Game of Life or Wolfram Codes (g/w)?: ";
    std::getline(std::cin, inputBuffer);
    inputHelper(inputBuffer, letter);

    int rows;
    int cols;
    GUIFileGOL guiFileGOL(width, height);
    GUIFileWolfram guiFileWolfram(width, height);
    bool preserve;

    if (letter == 'g') {
        // Prompt user for the filename
        std::cout << "Please enter the filename for Game of Life data: ";
        std::string filename;
        std::getline(std::cin, filename);

        std::cout << "Reading from file: " << filename << std::endl;
        guiFileGOL.readFileGOL(filename);
    } else if (letter == 'w') {
        std::cout << "Would you like to preserve past iterations on screen?(y/n): ";
        std::getline(std::cin, inputBuffer);
        char preserveInput;
        inputHelper(inputBuffer, preserveInput);
        preserve = (preserveInput == 'y');
        guiFileWolfram.preserve = preserve;
        guiFileWolfram.readInputWolfram();
    }

    std::cout << "Minimum seconds between generation: ";
    std::getline(std::cin, inputBuffer);
    int secondPerGen = inputHelperInt(inputBuffer);

    std::cout << "Press Q to quit.\n";
    screen.blitTo(windowSurface);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
            }
        }

        screen.clear();
        if (letter == 'g') {
            guiFileGOL.renderGOL(screen);
            std::this_thread::sleep_for(std::chrono::seconds(secondPerGen));
            guiFileGOL.iterateGenerationGOL();
        } else {
            guiFileWolfram.render(screen);
            std::this_thread::sleep_for(std::chrono::seconds(secondPerGen));
            guiFileWolfram.iterateGeneration();
        }

        screen.blitTo(windowSurface);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
