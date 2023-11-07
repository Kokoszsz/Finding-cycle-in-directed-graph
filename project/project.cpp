#include "source.h"


// main function
int main(int argc, char* argv[]) {


    std::string inputFileName;
    std::string outputFileName;

    NodeMap MY_MAP;
    DiscoveredCycles DISCOVERED_CYCLES;

    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " -g input_file -c output_file" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-g") {
            if (i + 1 < argc) {
                inputFileName = argv[i + 1];
                i++;
            }
            else {
                std::cerr << "Error: -g switch requires an input file name." << std::endl;
                return 1;
            }
        }
        else if (std::string(argv[i]) == "-c") {
            if (i + 1 < argc) {
                outputFileName = argv[i + 1];
                i++;
            }
            else {
                std::cerr << "Error: -c switch requires an output file name." << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "Usage: " << argv[0] << " -g input_file -c output_file" << std::endl;
            return 1;
        }
    }

    std::string edges;
    edges = get_data(inputFileName);
    edges += ',';
    std::cout << edges << std::endl;


    MY_MAP = create_map(edges);


    //for (const auto& entry : d) {
    //    std::cout << "Node " << entry.first << " connects to: ";
    //    for (int connected_node : entry.second) {
    //        std::cout << connected_node << " ";
    //    }
    //    std::cout << std::endl;
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
