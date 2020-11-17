/*
We will use test data in test_data.csv located in the util folder in the main
directory. The file has the data as follows
| Presented | Response |
|     1     |    2     |
|     2     |    4     |
|     3     |    5     |
|     4     |    1     |
|     5     |    3     |
*/

#include<Mahi/Util.hpp>

using namespace mahi::util;

int main(int argc, char* argv[]) {
    // sometimes you may want this to be an absolute filepath just to make sure.
    std::string filepath = "C:/Git/mahi-experiment/data/load_data/test_data.csv";
    
    // read back subset of header without offset
    // notice that this is an array here (not vector). It needs a size to read properly, and this is 
    // the easiest way. We could also add dummy values to a vector, but that is unnecessary
    std::array<std::string,2> headers_read;

    csv_read_row(filepath, headers_read, 0, 0);
    for (auto& header : headers_read){
        std::cout << header << ", ";
    }    
    std::cout << std::endl;

    // read back subset of data with one row offset (header) as ints
    std::array<std::array<int,2>,5> data;
    csv_read_rows(filepath, data, 1, 0);
    for (auto& data_row : data){
        for (auto& data_val : data_row){
            std::cout << data_val << ", ";
        }
        std::cout << std::endl;
    }
}