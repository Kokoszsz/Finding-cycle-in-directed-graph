#ifndef SOURCE_H
#define SOURCE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

// #include <algorithm>
// #include <functional>

using NodeMap = std::unordered_map<int, std::vector<int>>;
using DiscoveredCycles = std::vector<std::vector<int>>;

/**
 * This function parses command-line parameters to extract the input and output file paths.
 * It expects the parameters to be in the form of "-g input_file -c output_file".
 *
 * @param count The number of command-line parameters.
 * @param params An array of C-style strings representing command-line parameters.
 * @param input_file Reference to a std::string where the input file path will be stored.
 * @param output_file Reference to a std::string where the output file path will be stored.
 *
 * @return Returns true if the input and output file paths were successfully extracted,
 *         false otherwise. In case of failure, an error message is printed to std::cout.
 */
bool read_params(int count, const char* params[], std::string& input_file, std::string& output_file);


/**
 * This function reads data from the specified file and creates a NodeMap, where each
 * node is associated with a list of connected nodes. The file is expected to contain
 * lines representing edges in the format "from_node - to_node".
 *
 * @param filename The name of the file containing edge information.
 *
 * @return Returns a NodeMap representing the connectivity information read from the file.
 *         The NodeMap is a std::unordered_map<int, std::vector<int>>, where each key-value pair
 *         represents a node and its connected nodes.
 */
NodeMap get_data_and_create_map(const std::string& filenamet);

/**
 * This function performs a depth-first search (DFS) on every node in the graph
 * and stores the discovered cycles in the DISCOVERED_CYCLES vector.
 *
 * @param MY_MAP The graph represented as a NodeMap (adjacency list).
 * @param DISCOVERED_CYCLES Reference to a vector of vectors where discovered cycles are stored.
 */
void DFS_on_every_node(NodeMap& MY_MAP, DiscoveredCycles& DISCOVERED_CYCLES);

/**
 * This function performs a depth-first search (DFS) to find cycles in a graph starting from
 * a specified node. It populates the discovered cycles in the DISCOVERED_CYCLES vector.
 *
 * @param start_node The node from which the search for cycles begins.
 * @param cur_node The current node being explored during the search.
 * @param visited A vector representing the nodes visited during the current exploration.
 * @param MY_MAP The graph represented as a NodeMap (adjacency list).
 * @param DISCOVERED_CYCLES Reference to a vector of vectors where discovered cycles are stored.
 */
void DFS(const int start_node, const int cur_node, std::vector<int> visited, NodeMap& MY_MAP, DiscoveredCycles& DISCOVERED_CYCLES);

/**
 * This function takes a vector of discovered cycles and writes them to an output file.
 * Each cycle is represented as a space-separated sequence of node IDs.
 *
 * @param outputFileName The name of the output file where cycles will be saved.
 * @param DISCOVERED_CYCLES Reference to a vector of vectors containing discovered cycles.
 */
void save_data(std::string outputFileName, const DiscoveredCycles& DISCOVERED_CYCLES);

/**
 * This function prints the discovered cycles in the graph.
 *
 * @param DISCOVERED_CYCLES Reference to a vector of vectors containing the discovered cycles.
 */
void print_cycles(const DiscoveredCycles& DISCOVERED_CYCLES);

#endif
