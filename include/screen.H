/*
 * =====================================================================================
 *
 *       Filename:  screen.H
 *
 *    Description:  Include file for screen class
 *
 *        Version:  1.0
 *        Created:  03/25/2017 05:23:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aditya Raman
 *
 * =====================================================================================
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

namespace bakar
{
    class screen
    {
        public:
            const static int SCREEN_WIDTH = 800;
            const static int SCREEN_HEIGHT = 600;

        private:
            SDL_Window *m_window;
            SDL_Renderer *m_renderer;
            SDL_Texture *m_texture;
            Mix_Music *m_music;
            Uint32 *m_buffer1;
            Uint32 *m_buffer2;

        public:
            screen();
            bool init();
            void update();
            void setPixel(
                    int x,
                    int y,
                    Uint32 red,
                    Uint32 green,
                    Uint32 blue
                    );
            bool processEvents();
            void close();
            //void clear();
            void boxBlur();
            void loadMusic(const char *file);
    };
}

#endif
