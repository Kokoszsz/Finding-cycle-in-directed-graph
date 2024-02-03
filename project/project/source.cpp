#include "source.h"

bool read_params(int count, const char* params[], std::string& input_file, std::string& output_file)
{
    if (count != 5) {
        std::cout << "Usage: " << params[0] << " -g input_file -c output_file" << std::endl;
        return false;
    }

    bool has_g = false;
    bool has_c = false;

    for (int i = 1; i < count - 1; i += 2) {
        if (std::string(params[i]) == "-g") {
            if (i + 1 < count) {            
                input_file = params[i + 1];
                has_g = true;
            }
        }
        else if (std::string(params[i]) == "-c") {
            if (i + 1 < count) {
                output_file = params[i + 1];
                has_c = true;
            }
        }
    }

    if (!has_g || !has_c) {
        std::cout << "Usage: " << params[0] << " -g input_file -c output_file" << std::endl;
        return false;
    }

    return true;
}

NodeMap get_data_and_create_map(const std::string& filename)
{
    std::ifstream file(filename);
    NodeMap cur_map;
    std::string from_node = "";
    std::string to_node = "";
    bool arrow = false;
    bool comma = false;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            for (char c : line) {
                if (!arrow and !comma) {
                    if (std::isdigit(c)) {
                        from_node += c;
                    }
                    else if (c == '-' and !from_node.empty()) {
                        arrow = true;
                    }
                }
                else if (arrow and !comma) {
                    if (std::isdigit(c)) {
                        to_node += c;
                    }
                    else if (c == ',' and !to_node.empty()) {
                        comma = true;
                    }
                }

                // should not be possible
                //else if (!arrow and comma) {
                    //comma = false;
                //}

                else {
                    arrow = false;
                    comma = false;
                    // Check if to_node is already in cur_map[from_node]
                    if (std::find(cur_map[stoi(from_node)].begin(), cur_map[stoi(from_node)].end(), stoi(to_node)) == cur_map[stoi(from_node)].end()) {
                        cur_map[stoi(from_node)].push_back(stoi(to_node));
                    }
                    from_node = "";
                    to_node = "";
                    if (std::isdigit(c)) {
                        from_node += c;
                    }
                }

            }
        }
        if (!from_node.empty() and !to_node.empty()) {
            // Check if to_node is already in cur_map[from_node]
            if (std::find(cur_map[stoi(from_node)].begin(), cur_map[stoi(from_node)].end(), stoi(to_node)) == cur_map[stoi(from_node)].end()) {
                cur_map[stoi(from_node)].push_back(stoi(to_node));
            }
        }

        file.close();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
        exit(2);
    }

    return cur_map;
}

void DFS_on_every_node(NodeMap& MY_MAP, DiscoveredCycles& DISCOVERED_CYCLES) {
    std::vector<int> visited;
    for (const auto& entry : MY_MAP) {
        DFS(entry.first, entry.first, visited, MY_MAP, DISCOVERED_CYCLES);
        std::vector<int> nth;
        MY_MAP[entry.first] = nth;
    }
}

void DFS(const int start_node, const int cur_node, std::vector<int> visited, NodeMap& MY_MAP, DiscoveredCycles& DISCOVERED_CYCLES) {
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
        DFS(start_node, neighbour_node, visited, MY_MAP, DISCOVERED_CYCLES);
    }
}

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
        exit(2);
    }
}

void print_cycles(const DiscoveredCycles& DISCOVERED_CYCLES) {
    for (std::vector<int> cycle : DISCOVERED_CYCLES) {
        for (int i = 0; i < cycle.size(); i++) {
            std::cout << cycle[i];
            if (i < cycle.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}