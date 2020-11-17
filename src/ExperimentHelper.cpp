#include <ExperimentHelper.hpp>
#include <Mahi/Util.hpp>

using namespace mahi::util;

std::array<std::array<int,2>,5> load_data(std::string filepath){
    // read back subset of data with one row offset (header) as ints
    std::array<std::array<int,2>,5> data;
    if(!csv_read_rows(filepath, data, 1, 0)){
        //if the read fails, return everything as zeros which we can check
        data = {{{0,0},{0,0},{0,0},{0,0},{0,0}}};
    }
    return data;
}

void save_data(std::string filepath, std::vector<CollectData> data){

    std::vector<std::string> header = {"presented cue", "response cue", "response time", "session"};

    std::vector<std::vector<std::string>> save_data_string;

    for (size_t i = 0; i < data.size(); i++){
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