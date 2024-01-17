#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>

#include <simulator.hpp>

void showHelp() {
    std::cout << "Usage: ./sim [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help             Show help message" << std::endl;
    std::cout << "  -f, --feature-test     Features testing" << std::endl;
    std::cout << "  -l, --load-test        Load testing" << std::endl;
}

int main(int argc, char **argv) {    
    try {
        if(argc > 1) {
            std::string arg = argv[1];
            if (arg == "-h" || arg == "--help" || arg == "-help") {
                showHelp();
                return 0;
            } else {
                simulator* sim = new simulator();
                if (arg == "-f" || arg == "--feature-test" || arg == "-feature-test") {
                    std::cout << "Feature testing mode is running..." << std::endl;
                    sim->runFeatureTesting();
                } else if (arg == "-l" || arg == "--load-test" || arg == "-load-test") {
                    std::cout << "Load testing mode is running..."  << std::endl;
                    sim->runLoadTesting();
                }
            }
        } else {
            std::cout << "Invalid command. Use command \"sim -h\" for more detail options." << std::endl;
            return 0;
        }

        while(true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }

        std::cout << "Comlpleted." << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Exception caught" << std::endl;
    }
    return 0;
}
