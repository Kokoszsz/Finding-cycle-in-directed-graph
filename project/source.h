#include <unordered_map>
#include <iostream>

using NodeMap = std::unordered_map<int, std::vector<int>>;
using DiscoveredCycles = std::vector<std::vector<int>>;

NodeMap create_map(std::string conection_list);
void find_cycle(const int start_node, const int cur_node, std::vector<int> visited, NodeMap& MY_MAP, DiscoveredCycles& DISCOVERED_CYCLES);
std::string get_data(const std::string filename);
void save_data(std::string outputFileName, const DiscoveredCycles& DISCOVERED_CYCLES);
