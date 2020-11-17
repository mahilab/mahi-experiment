#include<Mahi/Util.hpp>

using namespace mahi::util;

int main(int argc, char* argv[]) {
    // create Options object
    Options options("options.exe", "Simple Program Demonstrating Options");

    // add options
    // options can be short, long, or both (short must come first)
    // for example:   options.exe -s 2  OR   options.exe --subject_number 2
    options.add_options()
        ("s,subject_number", "subject number for the experiment.", value<int>());

    // parse options
    auto result = options.parse(argc, argv);

    // initialize the subject number to some default
    int subject_number = 0;

    // if a subject number was input, write it to the variable subject_number.
    // otherwise, let the user know the subject number is the default value
    if (result.count("subject_number") > 0) {
        subject_number = result["subject_number"].as<int>();
        std::cout << "You input a subject number of: " << subject_number;
    }
    else{
        std::cout << "You did not input a subject number. Defaulting to 0";
    }

}