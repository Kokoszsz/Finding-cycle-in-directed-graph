#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include "source.h"



/**
 * Creates a map from input data where every node is a key, and its values are nodes that it leads to.
 *
 * This function takes an input connection list as a string and processes it to create a map where each node is a key,
 * and the values associated with each key represent the nodes that it leads to.
 *
 * @param connection_list A string containing comma-separated pairs representing connections between nodes.
 *                       Each pair should be in the format "from_node -> to_node".
 *
 * @return A NodeMap representing the connections between nodes, where the keys are the source nodes, and the values
 *         are vectors of destination nodes.
 */
NodeMap create_map(const std::string conection_list)
{
    std::string pair = "";
    NodeMap cur_map;
    for (auto x : conection_list) {
        if (x == ',') {
            std::string number = "";
            int from;
            int to;
            for (auto character : pair) {
                if (std::isdigit(character))
                    number += character;
                else if (!number.empty()) {
                    from = stoi(number);
                    number = "";
                }
            }
            if (!number.empty()) {
                to = stoi(number);
                cur_map[from].push_back(to);
            }
            pair = "";
        }
        else
            pair += x;

    }
    return cur_map;
}

/**
 * Finds cycles in a graph starting from a given node.
 *
 * This function recursively explores a graph to find cycles starting from the specified 'start_node'. When a cycle is found,
 * it is added to the 'DISCOVERED_CYCLES' container.
 *
 * @param start_node The node to start the cycle detection from.
 * @param cur_node The current node being explored in the graph.
 * @param visited A vector of visited nodes in the current path to 'cur_node'.
 * @param MY_MAP A reference to the NodeMap representing the graph.
 * @param DISCOVERED_CYCLES A container to store the discovered cycles in the graph.
 */
void find_cycle(const int start_node, const int cur_node, std::vector<int> visited, NodeMap& MY_MAP, DiscoveredCycles& DISCOVERED_CYCLES) {
    if (start_node == cur_node and visited.size() > 0) {
        visited.push_back(cur_node);
        DISCOVERED_CYCLES.push_back(visited);
        return;
    }
    for (const int visited_node : visited) {
        if (visited_node == cur_node) {
            return;
        }
    }

    visited.push_back(cur_node);
    for (const int neighbour_node : MY_MAP[cur_node]) {
        find_cycle(start_node, neighbour_node, visited, MY_MAP, DISCOVERED_CYCLES);
    }
}

/**
 * Reads data from a source file and stores it in a single string.
 *
 * This function opens the specified 'filename', reads the contents of the file, and removes whitespace characters.
 * The resulting data is returned as a single string.
 *
 * @param filename The name of the source file to read data from.
 * @return A string containing the data read from the file with whitespace characters removed.
 */
std::string get_data(const std::string& filename) {
    std::ifstream file(filename);

    std::string fileContent = "";
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::string result = "";
            for (char c : line) {
                if (!std::isspace(c)) {
                    result += c;
                }
            }
            fileContent += result;
        }

        file.close();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
    }

    return fileContent;
}

/**
 * Writes all discovered cycles into an output file. If no cycles are found, a message is written instead.
 *
 * This function takes a vector of discovered cycles 'DISCOVERED_CYCLES' and writes them to the specified 'outputFileName'.
 * If there are no cycles in the graph, it writes the message "There are no cycles in the graph." to the file.
 *
 * @param outputFileName The name of the output file where the cycles or a message will be written.
 * @param DISCOVERED_CYCLES A container holding the discovered cycles in the graph.
 */
void save_data(const std::string outputFileName, const DiscoveredCycles& DISCOVERED_CYCLES) {
    std::ofstream outputFile(outputFileName);

    if (outputFile.is_open()) {
        for (std::vector<int> cycle : DISCOVERED_CYCLES) {
            for (int i = 0; i < cycle.size(); i++) {
                outputFile << cycle[i];
                if (i < cycle.size() - 1) {
                    outputFile << " -> ";
                }
            }
            outputFile << std::endl;
        }

        if (DISCOVERED_CYCLES.size() <= 0)
            outputFile << "There are no cycles in the graph.";

        outputFile.close();
        std::cout << "Output has been written to 'output.txt'" << std::endl;
    }
    else {
        std::cerr << "Error opening the output file." << std::endl;
    }
}