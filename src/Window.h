#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "ErrorHandling.h"

class Window {
    public:
    Window() {
        //  Create window
        SDLWindow = SDL_CreateWindow(
            "Hello Window",
            getWidth(), 
            getHeight(),
            0
            //  SDL_WINDOW_RESIZABLE
        );
        #ifdef ERROR_LOGGING
        CheckSDLError( "Creating Window" );
        #endif
    }

    int getWidth() const {
        return 550;
    }

    int getHeight() const {
        return 700;
    }

    void render(){
        //  Get the window surface's pixel format details
        //  Ensures window surface is fully constructed before window surface update
        const auto* Fmt{
            SDL_GetPixelFormatDetails( getSurface()->format )
        };
        #ifdef ERROR_LOGGING
        CheckSDLError( "Getting Surface" );
        #endif

        /*
        const double now = ((double)SDL_GetTicks()) / 1000.0;
        const Uint8 redValue{ static_cast<Uint8>(0.5 + 0.5 * SDL_sin(now) ) };
        const Uint8 greenValue{ static_cast<Uint8>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3 ) ) };
        const Uint8 blueValue{ static_cast<Uint8>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3 ) ) };
        const Uint32 color{ SDL_MapRGBA( Fmt, nullptr, redValue, greenValue, blueValue, 200 ) };
        */
        
        Uint32 redBackground{};
        Uint32 greenBackground{};
        Uint32 blueBackground{};

        //  Check if alpha value for window surface is supported
        //  choice between RGBA or RGB for Uint32 'RedColor', 'GreenColor', 'BlueColor' values
        if (Fmt->Amask){
            //  std::cout << "Alpha is supported.\n";
            //  define pure Red color RGBA values
            redBackground = SDL_MapRGBA(
                Fmt,
                nullptr,
                255,    //  Red value
                0,      //  Green value
                0,      //  Blue value
                200     //  Alpha value
            );
            //  define pure Green color RGBA values
            greenBackground = SDL_MapRGBA(
                Fmt,
                nullptr,
                0,      //  Red value
                255,    //  Green value
                0,      //  Blue value
                200     //  Alpha value
            );
            //  define pure Blue color RGBA values
            blueBackground = SDL_MapRGBA(
                Fmt,
                nullptr,
                0,      //  Red value
                0,      //  Green value
                255,    //  Blue value
                200     //  Alpha value
            );
        }
        else {
            //  std::cout << "No Alpha support.\n";
            //  define pure Red color RGB values
            redBackground = SDL_MapRGB(
                Fmt,
                nullptr,    //  Pointer to pre-defined color palette, not used so passed nullptr
                255,        //  Red value
                0,          //  Green value
                0           //  Blue value
            );
            //  define pure Green color RGB values
            greenBackground = SDL_MapRGB(
                Fmt,
                nullptr,    //  Pointer to pre-defined color palette, not used so passed nullptr
                0,          //  Red value
                255,        //  Green value
                0           //  Blue value
            );
            //  define pure Blue color RGB values
            blueBackground = SDL_MapRGB(
                Fmt,
                nullptr,    //  Pointer to pre-defined color palette, not used so passed nullptr
                0,          //  Red value
                0,          //  Green value
                255         //  Blue value
            );
        }
    
        //  fill a rectangle by getting SDL surface associated with window, assigning to value, this case whole screen so nullptr, & define rectangle color
        SDL_FillSurfaceRect(
            getSurface(),   //  Get surface pixel format details
            nullptr,        //  Rectangle to fill, nullptr fills whole screen
            //  SDL_MapRGB(Fmt, nullptr, 255, 0, 0 )
            blueBackground  //  Color to fill background rectangle
        );

    }

    void update(){
        //  Update the window surface
        SDL_UpdateWindowSurface(SDLWindow);
    }

    SDL_Surface* getSurface() const {
        return SDL_GetWindowSurface(SDLWindow);
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    ~Window() {
        if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_DestroyWindow(SDLWindow);
        }
    }

    private:
    SDL_Window* SDLWindow{nullptr};
    
};
