/*
 * =====================================================================================
 *
 *       Filename:  main.C
 *
 *    Description:  Main source file
 *
 *        Version:  1.0
 *        Created:  03/25/2017 05:57:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aditya Raman
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "screen.H"
#include "swarm.H"

using namespace bakar;

int main()
{
    srand(time(NULL));

    screen parda;

    if (parda.init() == false)
    {
        cout << "ERROR initializing SDL" << endl;
    }

    parda.loadMusic("src/level32.ogg");

    swarm daandia;

    while(true)
    {
        //get colors to fade smoothly using sine
        int elapsed = SDL_GetTicks();
        //update the particles for this iteration
        daandia.updateSwarm(elapsed);

        int green = (sin(elapsed*0.0003) + 1)*128;
        int red = (sin(elapsed*0.0004) + 1)*128;
        int blue = (cos(elapsed*0.0005) + 1)*128;

        // create a bunch of particles randomly oriented on the screen
        const particle * const p_Particle = daandia.getParticle();
        for(int i=0; i<swarm::NPARTICLES; i++)
        {
            particle p = p_Particle[i];
            int x = (p.m_x + 1)*screen::SCREEN_WIDTH/2;
            int y = (p.m_y + 1)*screen::SCREEN_HEIGHT/2;

            parda.setPixel(x, y, red, green, blue);
        }

        parda.boxBlur();

        //update the screen
        parda.update();


        //check for messages/events
        if(parda.processEvents() == false)
        {
            break;
        }
    }

    parda.close();

    return 0;

}

