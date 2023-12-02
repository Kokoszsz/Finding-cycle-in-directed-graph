#include "my_head.h"
#include <fstream>
#include <sstream>
#include <algorithm>

GraphCycleDetector::GraphCycleDetector() {
    // Constructor if needed.
}

bool GraphCycleDetector::LoadGraph(const std::string& inputFilename) {
    // Define an adjacency list to represent the graph.
    // You may use a data structure like a vector of vectors.
    // Each vertex has a list of its outgoing edges.

    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file: " << inputFilename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int start, end;
        char arrow;

        if (iss >> start >> arrow >> end) {
            // Add an edge from start to end in your graph representation.
            // You may use a vector or another data structure to store this information.
        }
        else {
            std::cerr << "Error: Invalid input format in line: " << line << std::endl;
            return false;
        }
    }

    inputFile.close();
    return true;
}

std::vector<std::vector<int>> GraphCycleDetector::FindCycles() {
    // Implement cycle detection logic.
    // You can use standard graph algorithms like DFS to find cycles in the graph.
    // Remember to keep track of visited nodes and the current path during the traversal.
    // Store detected cycles in a vector of vectors.

    std::vector<std::vector<int>> cycles;
    // Your cycle detection code here.

    return cycles;
}

void GraphCycleDetector::SaveCycles(const std::string& outputFilename, const std::vector<std::vector<int>>& cycles) {
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the output file: " << outputFilename << std::endl;
        return;
    }

    if (cycles.empty()) {
        outputFile << "No cycles found in the graph." << std::endl;
    }
    else {
        for (const std::vector<int>& cycle : cycles) {
            for (int node : cycle) {
                outputFile << node << " -> ";
            }
            // To close the cycle, repeat the first node.
            outputFile << cycle.front() << std::endl;
        }
    }

    outputFile.close();
}
