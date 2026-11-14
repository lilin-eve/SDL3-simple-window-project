#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Rectangle {
    public:
    Rectangle( const SDL_Rect& rect ) 
    : rect{rect} {}

    void render( SDL_Surface* surface ) const {
        auto [ r, g, b, a ]{
            isMouseHovering ? hoverColor : normColor
        };
        
        const auto* Fmt{
            SDL_GetPixelFormatDetails(surface->format)
        };

        SDL_FillSurfaceRect(
            surface,
            &rect,
            SDL_MapRGB(Fmt, nullptr, r, g, b )
        );
    }

    void handleMouse( SDL_Event& mouse ){
        if ( mouse.type == SDL_EVENT_MOUSE_MOTION ){
            isMouseHovering = isWithinRect( (int)mouse.motion.x, (int)mouse.motion.y );
        }
        else if ( mouse.type == SDL_EVENT_MOUSE_BUTTON_DOWN ){
            if ( isMouseHovering && mouse.button.button == SDL_BUTTON_LEFT ){
                std::cout << "Rectangle left-clicked.\n";
                if ( mouse.button.clicks >= 2 ){
                    std::cout << "Rectangle double-clicked. :D WOAHHHHH!!!\n";
                }
            }
        }
        else if ( mouse.type == SDL_EVENT_WINDOW_MOUSE_LEAVE ){
            isMouseHovering = false;
        }
    }

    void setNormColor( const SDL_Color& newColor ){
        normColor = newColor;
    }

    SDL_Color getNormColor() const {
        return normColor;
    }

    void setHoverColor( const SDL_Color& newColor ){
        hoverColor = newColor;
    }

    SDL_Color getHoverColor() const {
        return hoverColor;
    }

    private:
    SDL_Rect rect;
    SDL_Color normColor{ 255, 125, 0, 255 };    //  Default Dark Orange
    SDL_Color hoverColor{ 128, 128, 0, 255 };   //  Default Olive

    bool isMouseHovering{false};

    bool isWithinRect( int x, int y ){
        if ( x < rect.x ){
            return false;
        }
        else if ( x > rect.x + rect.w ){
            return false;
        }
        else if ( y < rect.y ){
            return false;
        }
        else if ( y > rect.y + rect.h ){
            return false;
        }
        else {
            return true;
        }
    }

};
