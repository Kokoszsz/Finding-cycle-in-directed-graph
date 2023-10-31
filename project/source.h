#include <unordered_map>
#include <iostream>

extern std::unordered_map<int, std::vector<int>> MY_MAP;
extern std::vector<std::vector<int>> DISCOVERED_CYCLES;

std::unordered_map<int, std::vector<int>> adv_tokenizer(std::string s, std::string del, std::string del_2);
void find_cycle(int start_node, int cur_node, std::vector<int> visited);
std::string get_data(std::string filename);
void save_data(std::string outputFileName);
