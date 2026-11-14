#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <string>

//  Define variable below to enable error logging
//  #define ERROR_LOGGING

#ifdef ERROR_LOGGING
void CheckSDLError( const std::string& Action ){

    const char* Error{ SDL_GetError() };

    if ( *Error != '0' ){
        std::cout << "Error " << Action << ": " << Error << '\n';
        SDL_ClearError();
    }

}
#endif
