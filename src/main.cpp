#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "Rectangle.h"
#include "Window.h"
//  #include <SDL3_image/SDL_image.h>
//  #include <SDL3_ttf/SDL_ttf.h>

bool isRunning{true};

void handleMouseButtonEvents( SDL_MouseButtonEvent& mouseButton ){

    if ( mouseButton.button == SDL_BUTTON_LEFT && mouseButton.down && mouseButton.clicks >= 2 ){
        std::cout << "Left mouse button double clicked.\n";
    }
    else if ( mouseButton.button == SDL_BUTTON_LEFT ){
        if ( mouseButton.down ){
        std::cout << "Left mouse button pressed down . . .\n";
        }
        else {
        std::cout << " . . & left mouse button released.\n";
        }
    }
    else if ( mouseButton.button == SDL_BUTTON_RIGHT ) {
        if ( mouseButton.down ){
        std::cout << "Right mouse button pressed down . . .\n";
        }
        else {
        std::cout << " . . & right mouse button released.\n";
        }
    }
    else if ( mouseButton.button == SDL_BUTTON_MIDDLE ){
        if ( mouseButton.down ){
        std::cout << "Middle mouse button pressed down . . .\n";
        }
        else {
        std::cout << " . . & middle mouse button released.\n";            
        }
    }
    else if ( mouseButton.button == SDL_BUTTON_X1 ){
        if ( mouseButton.down ){
        std::cout << "Side mouse button 1 pressed down . . .\n";
        }
        else {
        std::cout << " . . & side mouse button 1 released.\n";           
        }
    }
    else if ( mouseButton.button == SDL_BUTTON_X2 ){
        if ( mouseButton.down ){
        std::cout << "Side mouse button 2 pressed down . . .\n";
        }
        else {
        std::cout << " . . & side mouse button 2 released.\n";            
        }
    }
}

void handleMouseMotion( Window& gameWindow, SDL_MouseMotionEvent& mouseEvent ){

    float distanceLeft{ mouseEvent.x };
    float distanceTop{ mouseEvent.y };
    float distanceRight{ gameWindow.getWidth() - mouseEvent.x };
    float distanceBottom{ gameWindow.getHeight() - mouseEvent.y };

    std::cout << "Mouse motion detected.\n";
    std::cout << "Distance from left: [" << distanceLeft << "], Distance from right: [" << distanceRight << "]\n";
    std::cout << "Distance from top: [" << distanceTop << "], Distance from bottom: [" << distanceBottom << "]\n";

}

//  definition for called function handleEvent()
//  
void handleEvent( SDL_Event& event ){

    

}

//  definition for caller function main()
//  
int main(int, char**){
    //  Initialization stage
    //  
    SDL_Init(SDL_INIT_VIDEO);   //  Initialize SDL video
    Window gameWindow;          //  Create variable 'gameWindow' from local class 'Window', located in 'Window.h'
    Rectangle rect{SDL_Rect{ ( gameWindow.getWidth() / 3 ), ( gameWindow.getHeight() / 3 ) , 200, 50 }};

    //  Loop application stage
    //  
    isRunning = true;
    SDL_Event event;

    while (isRunning){
        //  1. process Event objects
        //  use below, or SDL_PumpEvents() if event querying is irrelevant
        while ( SDL_PollEvent(&event) ){
            //  examine the Event object & react
            if ( event.type == SDL_EVENT_WINDOW_MOUSE_ENTER ){
                std::cout << "Mouse entered Window dimensions! :D \n";
            }
            else if ( event.type == SDL_EVENT_MOUSE_MOTION ){
                handleMouseMotion( gameWindow, event.motion );
                rect.handleMouse( event );
            }
            else if ( event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP ){
                handleMouseButtonEvents( event.button );
                rect.handleMouse( event );
            }
            else if ( event.type == SDL_EVENT_WINDOW_MOUSE_LEAVE ){
                std::cout << "Mouse left Window dimensions. :/ \n";
                rect.handleMouse( event );
            }
            else if ( event.type == SDL_EVENT_KEY_DOWN ){
                std::cout << "Keyboard button press detected.\n";
            }
            else if ( event.type == SDL_EVENT_QUIT ){
                std::cout << "Exiting SDL application . . . \n";
                isRunning = false;
            }   
        }
        //  2. update all objects

        //  3. render changes
        gameWindow.render();    //  render background color

        rect.render( gameWindow.getSurface() );

        gameWindow.update();    //  swap buffers
    }

    //  Shutdown stage
    //  
    SDL_Quit();

    return 0;
}
