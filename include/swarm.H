/*
 * =====================================================================================
 *
 *       Filename:  swarm.H
 *
 *    Description:  Include file for swarm class:-
 *                  Manages particle motion in the screen
 *
 *        Version:  1.0
 *        Created:  03/26/2017 03:37:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aditya Raman
 *
 * =====================================================================================
 */

#ifndef SWARM_H
#define SWARM_H

#include "particle.H"

namespace bakar
{
    class swarm
    {
        public:
            const static int NPARTICLES = 5000;

        private:
            particle *m_particles;
            int lastTime;

        public:
            swarm();
            ~swarm();
            const particle *const getParticle() {return m_particles;};
            void updateSwarm(int time);
    };
}

#endif
