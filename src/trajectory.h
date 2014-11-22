#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include <string>
#include "VECTOR.h"
#include "globals.h"

// TODO: Think about combining this with StatusInfo. 
// For now keep them separate as they serve separate porpoises.
struct TrajectoryNode
{
    TrajectoryNode() {}
    TrajectoryNode(VECTOR c, float u, float* j_angs) { com = c; uTorsoGlobAng = u; jointAngles = j_angs; }
    VECTOR com;
    float uTorsoGlobAng;
    float* jointAngles;

};

class Trajectory
{

    public:
        Trajectory() { size = 0; recordingTime = 0; }
        Trajectory(float t) { timestep = t; size = 0; recordingTime = 0; }


        float getTimestep() { return timestep; }
        int getSize() { return size; }
        float timelength() { return timestep*size; }

        float distance(Trajectory& other);

        std::vector<TrajectoryNode>& getTrajectoryInfo() { return trajectory; }

        void push(VECTOR pt, float uTor_ang, float* j_angs) { trajectory.push_back(TrajectoryNode(pt, uTor_ang, j_angs)); size++; }
        void pop() { if (trajectory.size() <= 0) { return; } trajectory.pop_back(); size--; }

        void setWriteName(std::string s) { ofname = s; }

        void writeToFile();
        void readFromFile(std::string);

        float getRecordingTime() { return recordingTime; }
        void incrementRecordingTime(float stepsize) { recordingTime += stepsize; }

        ~Trajectory();

    private:
        float timestep;
        int size;
        float recordingTime;

        std::string ofname;
        

//        std::vector<std::pair<VECTOR, float> > trajectory;
        std::vector<TrajectoryNode> trajectory;
};


#endif // TRAJECTORY_H
