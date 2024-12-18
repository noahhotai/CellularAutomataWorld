#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__
#include "../SDL_include/SDL.h"
#include "vec3.hpp"
#include "vec2.hpp"



// class ivec2;

class Screen
{
private:
    unsigned int width;
    unsigned int height;
    SDL_Surface* screenSurface; // Member to store the SDL_Surface pointer

public:
    Screen(unsigned int width, unsigned int height): width(width), height(height), screenSurface(nullptr)
    {
        // Create the SDL_Surface using the specified width and height
        screenSurface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        
        // Check if the surface was created successfully
        if (screenSurface == nullptr)
        {
            // Handle the error if the surface couldn't be created
            SDL_Log("Failed to create SDL_Surface: %s", SDL_GetError());
        }
    }
    ~Screen()
    {
        if (screenSurface != nullptr)
        {
            SDL_FreeSurface(screenSurface); // Free the surface when the object is destroyed
        }
    }


    static bool isPixelInsideTriangle(float x0, float y0,
                            float x1, float y1,
                            float x2, float y2,
                            float x3, float y3) {

        vec2 vecP0P1(x1 - x0, y1 - y0);
        vec2 vecP1P2(x2 - x1, y2-y1);
        float cross1 = vecP0P1.crossProduct(vecP1P2);


        vec2 vecP0P2(x2 - x0, y2 - y0);
        vec2 vecP2P3(x3 - x2, y3-y2);
        float cross2 = vecP0P2.crossProduct(vecP2P3);

        vec2 vecP0P3(x3 - x0, y3 - y0);
        vec2 vecP3P1(x1 - x3, y1 - y3);
        float cross3 = vecP0P3.crossProduct(vecP3P1);


        return ((cross1 >= 0) && (cross2 >= 0) && (cross3 >= 0)) || ((cross1 <= 0) && (cross2 <= 0) && (cross3 <= 0));
    }

    void drawTriangle(ivec2 v0, ivec2 v1, ivec2 v2, ivec3 color) {
        // Calculate bounding box for the triangle
        int minX = std::min({v0.x, v1.x, v2.x});
        int minY = std::min({v0.y, v1.y, v2.y});
        int maxX = std::max({v0.x, v1.x, v2.x});
        int maxY = std::max({v0.y, v1.y, v2.y});


        minX = std::max(minX, 0);
        minY = std::max(minY, 0);
        maxX = std::min(maxX, static_cast<int>(width) - 1);
        maxY = std::min(maxY, static_cast<int>(height) - 1);



        // Loop through each pixel in the bounding box
        for (int y = minY; y <= maxY; y++) {
            for (int x = minX; x <= maxX; x++) {
                ivec2 p(x, y);
                if (isPixelInsideTriangle(p.x, p.y, v0.x, v0.y, v1.x, v1.y, v2.x, v2.y)) {
                    this->colorPixel(p, color);
                }
            }
        }
    }
    void clear(){
        int i, j;
        for(i = 0; i < width; i++){
            for(j = 0; j < height; j++){
                this->colorPixel(ivec2(i, j), ivec3(0, 0, 0));
            }
        }
    }

    void colorPixel(ivec2 coordinates, ivec3 rgb){

        if (screenSurface == nullptr) {
            std::cerr << "Screen surface is not initialized.\n";
            return;
        }

        if (coordinates.x < 0 || coordinates.x >= width || coordinates.y < 0 || coordinates.y >= height)
        {
            // std::cout << "Pixel out of range.\n";
            return;
        }
        // Calculate the pixel location (depends on the surface format)
        unsigned int pixel = coordinates.y * width + coordinates.x;
         // Map the RGB values to the xworrect format for this surface
        unsigned int color = SDL_MapRGB(screenSurface->format, rgb.x, rgb.y, rgb.z);

        Uint32* pixelAddress = (Uint32*) screenSurface->pixels + pixel;
        
        *pixelAddress = color;
    }
    
    void fixMinMax(ivec2& min, ivec2& max){
        if (min.x > max.x) std::swap(min.x, max.x);
        if (min.y > max.y) std::swap(min.y, max.y);
    }
    void blitTo(SDL_Surface* destSurface, SDL_Rect* destRect = nullptr)
    {
        if (screenSurface == nullptr || destSurface == nullptr)
        {
            SDL_Log("Source or destination surface is null.");
            return;
        }

        // Perform the blit (copying the entire source surface to the destination surface)
        if (SDL_BlitSurface(screenSurface, nullptr, destSurface, destRect) < 0)
        {
            SDL_Log("Blit failed: %s", SDL_GetError());
        }
    }

    void drawBox(ivec2 min, ivec2 max, ivec3 color)
    {
        // Fix min and max coordinates
        fixMinMax(min, max);
        
        // Draw the box pixel by pixel
        for (int y = min.y; y <= max.y; y++)
        {
            for (int x = min.x; x <= max.x; x++)
            {
                this->colorPixel(ivec2(x, y), color);
            }
        }
    }


    void drawLineBresenham(ivec2 start, ivec2 end, ivec3 color)
    {
        int x1 = start.x;
        int y1 = start.y;
        int x2 = end.x;
        int y2 = end.y;

        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        int sx = (x1 < x2) ? 1 : -1;  // Step in the x direction
        int sy = (y1 < y2) ? 1 : -1;  // Step in the y direction
        int err = dx - dy;

        while (true)
        {
            // Color the current pixel
            if (x1 < width && x1 >= 0 && y1 < height && y1 >= 0){
                this->colorPixel(ivec2(x1, y1), color);
            }
            

            // Check if we have reached the end point
            if (x1 == x2 && y1 == y2)
                break;

            int e2 = 2 * err;

            // Adjust error and position
            if (e2 > -dy)
            {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y1 += sy;
            }
        }
    }
void plotCirclePoints(int cx, int cy, int x, int y, ivec3 color, bool fill = false)
{
    // Plot the perimeter points
    this->colorPixel(ivec2(cx + x, cy + y), color); // Octant 1
    this->colorPixel(ivec2(cx - x, cy + y), color); // Octant 2
    this->colorPixel(ivec2(cx + x, cy - y), color); // Octant 3
    this->colorPixel(ivec2(cx - x, cy - y), color); // Octant 4
    this->colorPixel(ivec2(cx + y, cy + x), color); // Octant 5
    this->colorPixel(ivec2(cx - y, cy + x), color); // Octant 6
    this->colorPixel(ivec2(cx + y, cy - x), color); // Octant 7
    this->colorPixel(ivec2(cx - y, cy - x), color); // Octant 8

    // If filling, draw horizontal lines between left and right bounds
    if (fill)
    {
        // Horizontal lines between left and right bounds for each segment
        for (int i = cx - x; i <= cx + x; i++)
        {
            this->colorPixel(ivec2(i, cy + y), color); // Top segment
            this->colorPixel(ivec2(i, cy - y), color); // Bottom segment
        }
        for (int i = cx - y; i <= cx + y; i++)
        {
            this->colorPixel(ivec2(i, cy + x), color); // Left segment
            this->colorPixel(ivec2(i, cy - x), color); // Right segment
        }
    }
}

void drawCircle(ivec2 center, int radius, ivec3 color)
{
    int x = 0;
    int y = radius;
    int d = 1 - radius; // Decision variable

    // Plot the initial points with filling
    plotCirclePoints(center.x, center.y, x, y, color, true);

    while (x < y)
    {
        x++;
        if (d < 0)
        {
            d += 2 * x + 1;
        }
        else
        {
            y--;
            d += 2 * (x - y) + 1;
        }
        plotCirclePoints(center.x, center.y, x, y, color, true);
    }
}



};
 
#endif
