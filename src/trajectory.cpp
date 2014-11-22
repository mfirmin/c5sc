

#include "trajectory.h"

#include <math.h>
#include <iostream>
#include <fstream>

void Trajectory::writeToFile()
{
    std::ofstream ofs;

    ofs.open(ofname);

    if (!ofs)
    {
        std::cerr << "Couldn't open trajectory file " << ofname << " for writing." << std::endl;
        return;
    }
    ofs << timestep << " " << size << std::endl;

    for (auto it = trajectory.begin(); it != trajectory.end(); it++)
    {
        ofs << it->com.x << " " << it->com.y << " " << it->com.z << " " << it->uTorsoGlobAng << std::endl;
        for (int i = 0; i < JOINT_COUNT; i++)
        {
            ofs << it->jointAngles[i] << " " << std::endl;
        }
    }
    ofs.close();
}

void Trajectory::readFromFile(std::string ifname)
{
    std::ifstream ifs;
    ifs.open(ifname);

    std::cout << "Reading Trajectory File: " << ifname << std::endl;

    if (!ifs)
    {
        std::cerr << "Couldn't open trajectory file " << ifname << " for reading." << std::endl;
        return;
    }

    ifs >> timestep >> size;

    std::cout << timestep << " " << size << std::endl;

    for (int i = 0; i < size; i++)
    {
        VECTOR temp;
        float tempf;
        ifs >> temp.x >> temp.y >> temp.z >> tempf;
        
        //this->push(temp, tempf);
        
        float* jangles = new float[JOINT_COUNT];
        for (int j = 0; j < JOINT_COUNT; j++)
        {
            ifs >> jangles[j];
        }


        trajectory.push_back(TrajectoryNode(temp, tempf, jangles));
    }

    ifs.close();


}


// TODO: Include Angular INFOR.
// Look into Frechet distance later  <-- Not convinced this would be better.
// For now, simple walk along both trajectories. (ie, time dependent) <-- imo this is better
float Trajectory::distance(Trajectory& other)
{

    dReal x_adjust = trajectory.front().com.x - other.trajectory.front().com.x;

    auto it = trajectory.begin();
    auto it2 = other.trajectory.begin();
    float retcom = 0, retuTor = 0, retangs = 0;

    int this_revs = 0;
    float this_ang_prev = 0;
    int other_revs = 0;
    float other_ang_prev = 0;
    
    while (true)
    {
//        VECTOR adjusted = VECTOR(it2->com.x + x_adjust, it2->com.y-.1, it2->com.z);
//        THIS VERSION IS NOT DEPENDENT ON X, ONLY Y
        VECTOR adjusted = VECTOR(((it2->com.x - other.trajectory.front().com.x)*1./2. + other.trajectory.front().com.x  + x_adjust), it2->com.y, it2->com.z);
        retcom += 100*it->com.distSq(adjusted);

        float this_ang = it->uTorsoGlobAng;
        float other_ang = it2->uTorsoGlobAng;
        if (this_ang_prev < PI && this_ang_prev > 2.57 && this_ang > -PI && this_ang < -2.57)
        {
            this_revs++;
        }
        else if (this_ang < PI && this_ang > 2.57 && this_ang_prev > -PI && this_ang_prev < -2.57)
        {
            this_revs--;
        }
        if (other_ang_prev < PI && other_ang_prev > 2.57 && other_ang > -PI && other_ang < -2.57)
        {
            std::cout << "up" << std::endl;
            other_revs++;
        }
        else if (other_ang < PI && other_ang > 2.57 && other_ang_prev > -PI && other_ang_prev < -2.57)
        {
            std::cout << "down" << std::endl;
            other_revs--;
        }

        this_ang_prev = this_ang;
        other_ang_prev = other_ang;


        float this_ang_with_revs = it->uTorsoGlobAng + 2*PI*this_revs;
        float other_ang_with_revs = it2->uTorsoGlobAng + 2*PI*other_revs;

        float ang = (this_ang_with_revs) - (other_ang_with_revs);

        retuTor += 1*pow((ang),2);
        for (int i = 0; i < JOINT_COUNT; i++)
        {
            retangs += 0*pow((it->jointAngles[i] - it2->jointAngles[i]), 2);
        }
        it++;
        it2++;
        if(it == trajectory.end() || it2 == other.trajectory.end())
            break;
    }

    float ret = retcom + retuTor + retangs;

    std::cout << "1: " << retcom << "\n2: " << retuTor << "\n3: " << retangs << std::endl;

    return ret;

}

Trajectory::~Trajectory()
{
    for (auto it = trajectory.begin(); it != trajectory.end(); it++)
    {
        delete [] (it->jointAngles);
    }
    trajectory.clear();
    size = 0;
    timestep = 0;
}
