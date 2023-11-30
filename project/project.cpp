#include "source.h"


// main function
int main(int argc, const char* argv[]) {


    std::string inputFileName;
    std::string outputFileName;

    NodeMap MY_MAP;
    DiscoveredCycles DISCOVERED_CYCLES;

    if (!read_params(argc, argv, inputFileName, outputFileName))
        exit(2);
    if (inputFileName.empty()) {
        std::cerr << "Error: No input file name provided" << std::endl;
        exit(2);
    }
    if (outputFileName.empty()) {
        std::cerr << "Error: No output file name provided" << std::endl;
        exit(2);
    }


    MY_MAP = get_data_and_create_map(inputFileName);


    //for (const auto& entry : MY_MAP) {
        //int key = entry.first;
        //const std::vector<int>& values = entry.second;
        //std::cout << "Key: " << key << ", Values: ";
        //for (int value : values) {
            //std::cout << value << ' ';
        //}

        //std::cout << std::endl;
    //}



    std::vector<int> visited;
    for (const auto& entry : MY_MAP) {
        find_cycle(entry.first, entry.first, visited, MY_MAP, DISCOVERED_CYCLES);
        std::vector<int> nth;
        MY_MAP[entry.first] = nth;
    }

    for (std::vector<int> cycle : DISCOVERED_CYCLES) {
        for (int i = 0; i < cycle.size(); i++) {
            std::cout << cycle[i];
            if (i < cycle.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
    save_data(outputFileName, DISCOVERED_CYCLES);


    return 0;
}
