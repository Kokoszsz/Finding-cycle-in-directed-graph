#include "source.h"


/** Main function, starting point for program execution

@param argc number of parameters when starting the program
@param argv an array of pointers to char arrays used when running the program

@return if the program executed successfully, 0 is returned
*/
int main(int argc, const char* argv[]) {


    std::string inputFileName;
    std::string outputFileName;

    NodeMap MY_MAP;
    DiscoveredCycles DISCOVERED_CYCLES;

    if (!read_params(argc, argv, inputFileName, outputFileName))
        exit(2);


    MY_MAP = get_data_and_create_map(inputFileName);


    DFS_on_every_node(MY_MAP, DISCOVERED_CYCLES);
  
    print_cycles(DISCOVERED_CYCLES);
    save_data(outputFileName, DISCOVERED_CYCLES);


    return 0;
}
