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
    // I am using the same set of fake data that we had in the collecting_data section. 
    //                          trial num           1           2          3          4          5
    std::vector<int> presented_cues     = {         1,          2,         3,         4,         5};
    std::vector<int> responded_cues     = {         2,          5,         3,         2,         1};
    std::vector<double> responded_times = {      1.50,       2.42,      3.53,      4.21,      1.23};
    std::vector<std::string> sessions   = {"training", "training", "testing", "testing", "testing"};

    std::vector<CollectData> data;
    // this would go somewhere in the loop that presents data and checks the response
    for (auto i = 0; i < presented_cues.size(); i++){
        CollectData data_set{presented_cues[i],responded_cues[i],responded_times[i],sessions[i]};
        data.push_back(data_set);
    }

    // container for header strings (could also be array<string> )
    std::vector<std::string> header = {"presented cue", "response cue", "response time", "session"};
    // this data to save must all be the same type. I could either make everything into a double and make
    // session something like 1.0 = train and 2.0 = test, but I will convert it all to string instead
    std::vector<std::vector<std::string>> save_data;

    // a trick I try to use when saving data is to add the time-stamp to the data. That way I never accidentally overwrite
    // data I didn't mean to (like if I input the wrong subject number or something). It is always better to keep extra data
    // than to accidentally delete something you didn't know you wanted. I would normally also add subject number or something
    // or even put it in a folder with the subject number name itself. You also may want to sometimes make this an absolute
    // filepath, i.e. C:/data/experiment/save_data/... just to make sure everything will work no matter where the executable is.
    Timestamp ts;
    std::string filepath = "../../../data/save_data/data_" + ts.yyyy_mm_dd_hh_mm_ss() + ".csv";

    // There are many ways I could have done this. I could have made the data into strings when I collected
    // the data, but the string conversion takes a bit of time (probably not enough to be significant in this)
    // experiment though. Instead, I am converting everything to strings when I am saving the data.
    std::vector<std::vector<std::string>> save_data_string;
    for (size_t i = 0; i < presented_cues.size(); i++){
        // get data for a single row (as a string vector)
        std::vector<std::string> save_data_string_row;
        save_data_string_row.push_back(std::to_string(data[i].presented_cue));
        save_data_string_row.push_back(std::to_string(data[i].response_cue));
        save_data_string_row.push_back(std::to_string(data[i].response_time));
        save_data_string_row.push_back(data[i].session);

        //add the entire new row to our vector of string vector data structure (2d string vector)
        save_data_string.push_back(save_data_string_row);
    }

    // write the header (just a row of strings, after all)
    csv_write_row(filepath, header);    
    // append the data
    csv_append_rows(filepath, save_data_string);

    print("Data saved to {}!",filepath);
}