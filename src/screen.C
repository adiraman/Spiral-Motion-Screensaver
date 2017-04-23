/*
 * =====================================================================================
 *
 *       Filename:  screen.C
 *
 *    Description:  Source file for screen class
 *
 *        Version:  1.0
 *        Created:  03/25/2017 05:31:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aditya Raman
 *
 * =====================================================================================
 */

#include "screen.H"

namespace bakar
{
    // Constructor
    screen::screen():
        m_window(NULL),
        m_renderer(NULL),
        m_texture(NULL),
        m_music(NULL),
        m_buffer1(NULL),
        m_buffer2(NULL)
    {

    }

    bool screen::init()
    {
        // Initialize SDL:-
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            cout << "SDL Init failed, Error code : " << SDL_GetError() << endl;
            return false;
        }

        // create an SDL window:-
        m_window = SDL_CreateWindow(
                " ", // window title
                SDL_WINDOWPOS_UNDEFINED,   // initial x pos
                SDL_WINDOWPOS_UNDEFINED,   // initial y pos
                SCREEN_WIDTH,              // width in pixels
                SCREEN_HEIGHT,             // height in pixels
                SDL_WINDOW_SHOWN           // flags
                );

        // Check to see if the window is allocated
        if(m_window == NULL)
        {
            cout << "Could not create window, Error code : " << SDL_GetError() << endl;
            SDL_Quit();
            return false;
        }

        // Create a renderer:-
        m_renderer = SDL_CreateRenderer(
                m_window,                     // window where rendering is displayed
                -1,                         // index, -1 initializes the 1st support
                SDL_RENDERER_PRESENTVSYNC   // flags
                );

        // check to see if renderer is allocated
        if(m_renderer == NULL)
        {
            cout << "Could not create renderer, Error code : " << SDL_GetError() << endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

    // Create Texture:-
        m_texture = SDL_CreateTexture(
                m_renderer,                   // renderering context
                SDL_PIXELFORMAT_RGBA8888,   // format (no of possible args)
                SDL_TEXTUREACCESS_STATIC,   // access
                SCREEN_WIDTH,               // width of texture in pixels
                SCREEN_HEIGHT               // height of texture in pixels
                );

        // check to see if texture is allocated
        if(m_texture == NULL)
        {
            cout << "Could not create texture, Error code : " << SDL_GetError() << endl;
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        //Allocate memory to all the pixels in the screen:-
        m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

        //initialize SDL mixer
        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            cout << "Could not initialize SDL mixer" << endl;
            return false;
        }

        return true;
    }

    void screen::update()
    {
        // Update texture with new pixel data
        SDL_UpdateTexture(
                m_texture,                    //texture to update
                NULL,                       //struct repr area to update.NULL for entire screen
                m_buffer1,                     //raw pixel data
                SCREEN_WIDTH*sizeof(Uint32) //no of bytes in a row of pixel data
                );

        // Clear rendering target with the drawing color
        SDL_RenderClear(m_renderer);

        // Copy the texture to current rendering target
        SDL_RenderCopy(
                m_renderer,       //rendering context
                m_texture,        //source texture
                NULL,           //source SDL_Rect NULL for entire texture
                NULL            //destination SDL_Rect NULL for entire texture
                );

        // Update the screen with any rendering performed
        SDL_RenderPresent(m_renderer);

    }

    void screen::setPixel(
            int x,      //X pos
            int y,      //Y pos
            Uint32 red,  //red color
            Uint32 green,//green color
            Uint32 blue  //blue color
            )
    {

        if(x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
        {
            return;
        }

        Uint32 color = 0;
        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;

        m_buffer1[(y*SCREEN_WIDTH) + x] = color;
    }

    bool screen::processEvents()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                return false;
            }
            // if a key was pressed
            else if(event.type == SDL_KEYDOWN)
            {
                //if 9 was pressed
                if(event.key.keysym.sym == SDLK_9)
                {
                    //if there is no music playing
                    if(Mix_PlayingMusic() == 0)
                    {
                        //play music
                        if(Mix_PlayMusic(m_music, -1) == -1)
                        {
                            return 1;
                        }
                    }
                    // if music is playing
                    else
                    {
                        //if music is paused
                        if(Mix_PausedMusic() == 1)
                        {
                            //Resume music
                            Mix_ResumeMusic();
                        }
                        //if music is playing
                        else
                        {
                            //pause music
                            Mix_PauseMusic();
                        }
                    }
                }
                // is 0 is pressed
                else if( event.key.keysym.sym == SDLK_0 )
                {
                    Mix_HaltMusic();
                }
            }
        }
        return true;
    }

    void screen::close()
    {
		delete [] m_buffer1;
        delete [] m_buffer2;
    	SDL_DestroyRenderer(m_renderer);
    	SDL_DestroyTexture(m_texture);
    	SDL_DestroyWindow(m_window);
        Mix_FreeMusic(m_music);
        Mix_CloseAudio();
        SDL_Quit();
    }

/*  void screen::clear()
    {
        memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    } */

    void screen::boxBlur()
    {
        //switch the buffers
        Uint32 *temp = m_buffer1;
        m_buffer1 = m_buffer2;
        m_buffer2 = temp;

        for(int y=0; y<SCREEN_HEIGHT; y++)
        {
            for (int x=0; x<SCREEN_WIDTH; x++)
            {
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                for(int row=-1; row<=1; row++)
                {
                    for(int col=-1; col<=1; col++)
                    {
                        int currentX = x + col;
                        int currentY = y + row;

                        if(currentX >=0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT)
                        {
                            Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];
                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }

                Uint8 red = redTotal/9;
                Uint8 green = greenTotal/9;
                Uint8 blue = blueTotal/9;

                setPixel(x, y, red, green, blue);
            }
        }
    }

    void screen::loadMusic(const char *file)
    {
        m_music = Mix_LoadMUS(file);

        if(m_music == NULL)
        {
            cout << "Error loading music file" << endl;
        }
    }
}

