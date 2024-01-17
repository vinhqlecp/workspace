#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

// Boost libraries
#include <boost/program_options.hpp>

// Data providers
#include <VehicleDataProvider.h>

using namespace std;
using namespace boost::program_options;

int parse_config(int argc, char **argv) {
    // Configuration file name
    string commonConfig;

    options_description desc("Open V2X options");
    desc.add_options ()
        ("help,h", "Print all available options")
        ("common-config", value(&commonConfig), "Path to v2x common config");
    // Parse command line arguments
    variables_map vm;
    store (command_line_parser (argc, argv).options (desc).run (), vm);
    notify (vm);

    if (vm.count ("help") || !vm.count ("common-config")) {
        cerr << desc << "\n";
        return -1;
    }
    return 0;
}

int main(int argc, char **argv) {
    int ret = 0;

    shared_ptr<VehicleDataProvider> locPtr(new VehicleDataProvider);
    locPtr->Start();

    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }

    return ret;
}