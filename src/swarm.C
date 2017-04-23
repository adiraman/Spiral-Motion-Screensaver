/*
 * =====================================================================================
 *
 *       Filename:  swarm.C
 *
 *    Description:  source file for class swarm
 *
 *        Version:  1.0
 *        Created:  03/26/2017 03:42:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Aditya Raman
 *
 * =====================================================================================
 */
#include "swarm.H"

namespace bakar
{
    swarm::swarm():lastTime(0)
    {
        m_particles = new particle[NPARTICLES];
    }

    swarm::~swarm()
    {
        delete [] m_particles;
    }

    void swarm::updateSwarm(int time)
    {
        int interval = time - lastTime;

        for(int i=0; i<NPARTICLES; i++)
        {
            m_particles[i].updateParticle(interval);
        }

        lastTime = time;
    }
}

