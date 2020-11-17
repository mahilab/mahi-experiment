#include <Mahi/Util.hpp>
#include <ExperimentHelper.hpp>
#include <algorithm>
#include <random>

using namespace mahi::util;

// create global stop variable CTRL-C handler function
ctrl_bool stop(false);
bool handler(CtrlEvent event) {
    stop = true;
    return true;
}

int main(int argc, char* argv[]) {
    // this gives precident to cancel the program using ctrl+c
    register_ctrl_handler(handler);

    // create Options object
    Options options("experiment.exe", "Simple Matching Experiment");

    options.add_options()
        ("s,subject_number", "subject number for the experiment.", value<int>());

    // parse options
    auto result = options.parse(argc, argv);


    ////// GET SUBJECT NUMBER //////
    // initialize the subject number to some default
    int subject_number;

    // if a subject number was input, write it to the variable subject_number.
    // otherwise, Exit the program because it was probably a mistake!
    if (result.count("subject_number") > 0) {
        subject_number = result["subject_number"].as<int>();
        std::cout << "You input a subject number of: " << subject_number << std::endl;
    }
    else{
        std::cout << "You did not input a subject number. Exiting the program";
        return -1; // returns early. This is exiting the main() function
    }

    ////// GET MAPPING FOR THE SUBJECT //////

    std::string filepath = "C:/Git/mahi-experiment/data/load_data/S" + std::to_string(subject_number) + ".csv";

    auto subject_mapping = load_data(filepath);

    if (subject_mapping[0][0] == 0 && subject_mapping[0][1] == 0){
        print("You did not successfully read from {}. Exiting the program.", filepath);
        return -1;
    }
    else{
        print("Successfully read from {}.", filepath);
    }

    std::vector<int> presentations;
    std::vector<int> responses;
    for (size_t i = 0; i < subject_mapping.size(); i++){
        presentations.push_back(subject_mapping[i][0]);
        responses.push_back(subject_mapping[i][1]);
    }

    ////// INITIALIZE VARIABLES TO USE FOR PRESENTATIONS //////

    int num_presentations = subject_mapping.size();
    
    // generate list of indices to use, i.e. 0,1,2,3,4 to refer to variables in mapping 
    // array. these will be randomized throughout the process.
    std::vector<int> indices;
    for (size_t i = 0; i < num_presentations; i++){
        indices.push_back(i);
    }

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(indices), std::end(indices), rng);

    int trial_number = 0;

    ////// INITIALIZE VARIABLES TO USE FOR DATA COLLETION //////

    std::vector<std::string> session_strings = {"Training", "Testing"};

    std::vector<CollectData> data;

    ////// INITIALIZE TIMING ELEMENTS //////

    // times that we will use for the two session times
    Time train_time = seconds(60);
    Time  test_time = seconds(2*60);

    // make a vector so that I can access the times using session_times[current_session]
    std::vector<Time> session_times = { train_time , test_time };

    Session current_session = training;

    Clock session_clock;
    Clock trial_clock;


    ////// MAIN LOOP //////

    // if the session clock expires, exit the loop and end the section. Note that if the session clock expires in training,
    // it will just restart given if statement at the end of the while loop, so it must be the testing section for this to exit
    cls();
    print("Starting Training session. You have {} seconds.\n", train_time.as_seconds());

    while ( session_clock.get_elapsed_time() < session_times[current_session] && !stop){        
        int trial_index = indices[trial_number % num_presentations];
        
        print("Time remaining: {} seconds.\n\nPresented cue: {}", (session_times[current_session]-session_clock.get_elapsed_time()).as_seconds(), presentations[trial_index]);

        // restart the trial clock so that we can get the time when someone hits "C"
        trial_clock.restart();
        
        // check response and wait 
        int answer = -1;
        while (std::find(responses.begin(), responses.end(), answer) == responses.end()){
            // if answer is -1, it means that the user hasn't responded yet, so don't bother 
            // them with long, unnecessary prompt
            if (answer == -1){
                std::cout << "Response: ";
            }
            // but if they mess up, remind them that the number has to be in the appropriate range
            else{
                std::cout << "Please respond with a number between " << min_element(responses) << " and " << max_element(responses) << ": ";
            }
            
            // this returns a 'key code', so we need to subtract by the char value of '0' (48)
            answer = get_key()-(int)'0';
            std::cout << answer << std::endl;

            if (answer + (int)'0'== (int)KEY_ESCAPE){
                return -1;
            }
        }

        ////// STORE DATA //////
        CollectData data_set{presentations[trial_index],responses[trial_index],trial_clock.get_elapsed_time().as_seconds(),session_strings[current_session]};
        data.push_back(data_set);

        ////// PROVIDE FEEDBACK //////
        // let them know if they were correct or incorrect (only in training)
        if(current_session == training){
            if (answer == responses[trial_index]){
                print("That was correct! The correct response to {} is {}\n", presentations[trial_index], responses[trial_index]);
            }
            else {
                print("That was incorrect! The correct response to {} is {}\n", presentations[trial_index], responses[trial_index]);
            }
        }
        else{
            cls();
        }
        
        ////// RANDOMIZE FOR NEXT ROUND IF NECESSARY //////
        // if trial number is multiple of 5, shuffle the list. This means that every time
        // we go through the list, we shuffle. This means we get the same amount of 
        // trials with all numbers
        trial_number++;
        if (trial_number % 5 == 0){
            std::shuffle(std::begin(indices), std::end(indices), rng);
        }

        ////// CHECK IF TIME LIMIT REACHED //////
        // if the session timing is up and the current session is trianing, reset session clock and change the session to "testing"
        if (session_clock.get_elapsed_time() > session_times[current_session] && current_session == training){
            cls();

            trial_number = 0;
            std::shuffle(std::begin(indices), std::end(indices), rng);
            
            print("Starting Testing session. You have {} seconds.\n", test_time.as_seconds());
            current_session = testing;
            session_clock.restart();
        }
    }
    
    ////// SAVE DATA //////
    Timestamp ts;
    std::string save_filepath = "C:/Git/mahi-experiment/data/save_data/S" + std::to_string(subject_number) + "data_" + ts.yyyy_mm_dd_hh_mm_ss() + ".csv";
    save_data(save_filepath, data);

    return 0;
}