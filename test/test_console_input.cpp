#include<Mahi/Util.hpp>

using namespace mahi::util;

int main(int argc, char* argv[]) {

    // An example mapping to use for testing. The use of the presented vector
    // is not necessary and can be done cleaner, but used here to be explicit
    std::vector<int> presented {1, 2, 3, 4, 5};
    std::vector<int> response  {2, 4, 5, 1, 3};

    std::vector<int> user_answers;
    for (auto i = 0; i < presented.size(); i++){
        // note there are several ways to print to console as a part of mahi-util. see ex_print.cpp in mahi-util for examples
        // while std::cout is the most basic way (but also provides the most flexibility with more effort)
        print("Presented cue: {}", presented[i]);
        
        // I didn't want to take an invalid answer (i.e. not 1-5, and not a random letter or something),
        // so I run this while loop until I get an answer that is part of the response set. Note I start
        // with answer of -1 so that it always runs the loop at least once. I didn't know how to do this,
        // but I found it by googling "check if number part of a vector c++" (it is the second answer).
        // Also note that there could be easier solutions, i.e. 0 < answer < 5, but that won't necessarily work
        // if you have non-continuous sets or the values change. This works regardless of the response list.
        // https://www.techiedelight.com/check-vector-contains-given-element-cpp/#:~:text=The%20simplest%20solution%20is%20to,using%20std%3A%3Acount%20function.
        int answer = -1;
        while (std::find(response.begin(), response.end(), answer) == response.end()){
            std::cout << "Please respond with a number between " << min_element(response) << " and " << max_element(response) << ": ";
            
            // this returns a 'key code', so we need to subtract by the char value of '0' (48)
            // there are other ways to do this, but this was working well error checking for
            // me so I am sticking with it. You could also use cin, but that was weird when I
            // was putting in a letter key
            answer = get_key()-(int)'0';
            std::cout << answer << std::endl;
        }

        // add the answer to the user_answers vector in the 'i'th place
        user_answers.push_back(answer);

        // let them know if they were correct or incorrect
        if (user_answers[i] == response[i]){
            print("That was correct! The correct response to {} is {}\n", presented[i], response[i]);
        }
        else {
            print("That was incorrect! The correct response to {} is {}\n", presented[i], response[i]);
        }
    }
}