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

bool read_params(int count, const char* params[], std::string& input_file, std::string& output_file);
NodeMap get_data_and_create_map(const std::string& filenamet);
void find_cycle(const int start_node, const int cur_node, std::vector<int> visited, NodeMap& MY_MAP, DiscoveredCycles& DISCOVERED_CYCLES);
void save_data(std::string outputFileName, const DiscoveredCycles& DISCOVERED_CYCLES);

#endif
