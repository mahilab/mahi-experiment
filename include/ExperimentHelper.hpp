#include <string>
#include <vector>

// custom struct to store our data for a single round
struct CollectData{
    int presented_cue;
    int response_cue;
    double response_time;
    std::string session;
};

// enum so that I can use training/testing instead of ambiguous 0 and 1
enum Session{
    training, // 0
    testing   // 1
};

// Save data given a vector of the CollectData structure and a filepath.
// Each component of data is converted to a string before it is saved.
void save_data(std::string filepath, std::vector<CollectData> data);

// This loads data given a valid filepath and saves it into a 2d array
// of size 5x2 with the first column corresponding to the presented cue
// and the second column corresponding to the correct response cue.
std::array<std::array<int,2>,5> load_data(std::string filepath);