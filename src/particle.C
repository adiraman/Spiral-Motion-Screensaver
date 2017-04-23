/*
 * =====================================================================================
 *
 *       Filename:  particle.C
 *
 *    Description:  source file for class particle
 *
 *        Version:  2.0
 *        Created:  03/26/2017 06:33:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aditya Raman
 *
 * =====================================================================================
 */

#include "particle.H"
#include "screen.H"

namespace bakar
{
    particle::particle()
    {
        init();
    }

    void particle::init()
    {
        m_x = 0;
        m_y = 0;

        m_direction = (2*M_PI*rand())/RAND_MAX;
        m_speed = (0.02*rand())/RAND_MAX;
        m_speed *= m_speed;
    }

    particle::~particle()
    {

    }

    void particle::updateParticle(int interval)
    {
        m_direction += interval*0.0002;

        double xSpeed = m_speed*cos(m_direction);
        double ySpeed = m_speed*sin(m_direction);

        m_x += xSpeed*screen::SCREEN_HEIGHT/screen::SCREEN_WIDTH*interval;
        m_y += ySpeed*interval;

        if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
        {
            init();
        }

        if(rand() < RAND_MAX/100)
        {
            init();
        }
    }
}

