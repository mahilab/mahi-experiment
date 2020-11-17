#include<Mahi/Util.hpp>

using namespace mahi::util;

// enum so that I can use training/testing instead of ambiguous 0 and 1
enum Session{
    training, // 0
    testing   // 1
};

int main(int argc, char* argv[]) {
    std::vector<std::string> session_strings = {"Training", "Testing"};
    
    // times that we will use for the two session times
    Time train_time = seconds(10);
    Time  test_time = seconds(15);

    // make a vector so that I can access the times using session_times[current_session]
    std::vector<Time> session_times = { train_time , test_time };

    Session current_session = training;

    Clock session_clock;
    Clock trial_clock;

    print("Starting Training session. You have {} seconds.\n", train_time.as_seconds());

    // if the session clock expires, exit the loop and end the section. Note that if the session clock expires in training,
    // it will just restart given if statement at the end of the while loop, so it must be the testing section for this to exit
    while ( session_clock.get_elapsed_time() < session_times[current_session]){
        print("Press \"C\" to print the current time.\nIf it is after the alotted session time, the session will end.");
        
        // restart the trial clock so that we can get the time when someone hits "C"
        trial_clock.restart();
        
        // wait until the 'C' key is pressed
        while(get_key() != 'c'){};
        
        print("Session: {}", session_strings[current_session]);
        print("Trial time: {} seconds. Session time remaining: {} seconds.\n", trial_clock.get_elapsed_time().as_seconds(), (session_times[current_session]-session_clock.get_elapsed_time()).as_seconds());

        // if the session timing is up and the current session is trianing, reset session clock and change the session to "testing"
        if (session_clock.get_elapsed_time() > session_times[current_session] && current_session == training){
            cls();
            print("Starting Testing session. You have {} seconds.\n", test_time.as_seconds());
            current_session = testing;
            session_clock.restart();
        }
    }
}