/*
 * =====================================================================================
 *
 *       Filename:  particle.H
 *
 *    Description:  Include file for particle class
 *
 *        Version:  2.0
 *        Created:  03/26/2017 06:32:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aditya Raman
 *
 * =====================================================================================
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include <math.h>
#include <stdlib.h>

using namespace std;
namespace bakar
{
    struct particle
    {
        double m_x;
        double m_y;

        private:
            double m_speed;
            double m_direction;

        private:
            void init();

        public:
            particle();
            ~particle();
            void updateParticle(int interval);
    };
}


#endif
