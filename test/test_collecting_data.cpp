/*
The data we want to collect is 
    presented cue
    response cue
    response time
    session (training or testing)

so make a custom type that will hold that and test out using it
*/

#include<Mahi/Util.hpp>

// custom struct to store our data for a single round
struct CollectData{
    int presented_cue;
    int response_cue;
    double response_time;
    std::string session;
};

using namespace mahi::util;

int main(int argc, char* argv[]) {
    // we will need to store a vector of these data structures, so lets initialize that
    std::vector<CollectData> data;

    // lets make some fake data 
    //                          trial num           1           2          3          4          5
    std::vector<int> presented_cues     = {         1,          2,         3,         4,         5};
    std::vector<int> responded_cues     = {         2,          5,         3,         2,         1};
    std::vector<double> responded_times = {      1.50,       2.42,      3.53,      4.21,      1.23};
    std::vector<std::string> sessions   = {"training", "training", "testing", "testing", "testing"};

    // this would go somewhere in the loop that presents data and checks the response
    for (auto i = 0; i < presented_cues.size(); i++){
        // create new CollectData variable with the current values and add it to the data vector
        CollectData data_set{presented_cues[i],responded_cues[i],responded_times[i],sessions[i]};
        data.push_back(data_set);
    }

    // print out the data to make sure we got what we wanted.
    for (size_t i = 0; i < data.size(); i++){
        print("Prented: {}, Response: {}, Time: {}, Session: {}", data[i].presented_cue, data[i].response_cue, data[i].response_time, data[i].session);
    }
}