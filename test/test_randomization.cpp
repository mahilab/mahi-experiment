// didnt know how to do this, but found the answer here
// https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

#include <Mahi/Util.hpp>
#include <algorithm>
#include <random>

using namespace mahi::util;

int main(int argc, char* argv[]) {
   std::vector<int> presented {1, 2, 3, 4, 5};

    auto rng = std::default_random_engine {};

    // shuffle and print presented vector 10 times. Wait for a key-press each time
    for (size_t i = 0; i < 10; i++){

        std::shuffle(std::begin(presented), std::end(presented), rng);
        print_var(presented);
        
        get_key();
    }
    
}