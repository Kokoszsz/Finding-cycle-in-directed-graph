#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include "source.h"



// takes input data creates a map. every node is a key and its values are node that it leads to
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

// finds cycles in a graph
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

// takes data from source file and puts into single string
std::string get_data(const std::string filename) {
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

// writes all found cycle into output file. if there are no cycles "There are no cycles in the graph." message is written instead
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