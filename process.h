/*

Relationship between IOEvent::time and Process time:

IOEvent::time represents the number of time steps into a process execution that
an IO Event will occur. This value will be relative to Process::processorTime.

For example, if a Process has an IOEvent with a time value of 10, then that means 
that when the process hits it's 10th time step (i.e., Process::processorTime = 10)
it should enter a blocked state for IOEvent::duration time steps.

*/

#pragma once

#include<iostream>
#include<list>
#include<vector>
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;

struct IOEvent
{
    IOEvent() :  id(9999999), time(-1), resourceId(99999) {};
    IOEvent(const int& t, const unsigned int& duration, const unsigned int& newId, const unsigned int& recId) : id(newId), time(t), dur(duration), resourceId(recId) {}

    unsigned int id;

    long time;                  // The time the event occurs during the process execution
    int dur;                   // how long the resource will be held for
    unsigned int resourceId;    // The id of the resource associated with this request
};

enum State { ready, processing, blocked, newArrival, done }; // Used to track the process states

struct Process
{
    Process() : id(999999), arrivalTime(-1), doneTime(-1), reqProcessorTime(0), processorTime(0), state(newArrival), affinity(-1) {}

    unsigned int id;        // The process ID, assigned when the process is admitted to the system

    long arrivalTime;       // When the process will start/become runnable
    long doneTime;          // Convenience variable, use this to keep track of when a process completes
    long reqProcessorTime;  // Total amount of processor time needed
    long processorTime;     // Amount of processor given to this process

    State state; // State of the process
    vector<int> otherResourcesIds; // resources this process has allocated to it
    short affinity; // The last processor the process was run on, -1 if it hasn't been run on any processor yet 

    list<IOEvent> ioEvents;  // The IO events for this process, stored in order of the time into the process execution that they start 

    void printProcess()
    {
        cout << setw(2) << arrivalTime << " |";
        cout << setw(3) << doneTime << " |";
        cout << setw(5) << reqProcessorTime << " |";
        cout << setw(3) << processorTime << " |"; 
        cout << setw(2) << state << " |";

        for (auto & event : ioEvents)
        {
            cout << " " << event.time << ", " << event.resourceId << ";";
        }

        cout << endl;
    }
};

// Print the state of all the processes in the vector
void printProcessStates(list<Process>& processVector);

// Print all information about all processes from a vector (debugging function)
void printProcessSet(vector<Process>& processVector);

