#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <sstream>

std::unordered_map<int, std::vector<int>> MY_MAP;
std::vector<std::vector<int>> DISCOVERED_CYCLES;


std::unordered_map<int, std::vector<int>> adv_tokenizer(std::string s, std::string del, std::string del_2)
{
    std::string pair = "";
    std::unordered_map<int, std::vector<int>> cur_map;
    for (auto x : s) {
        pair += x;
        if (x == ',') {
            std::string number = "";
            int from;
            int to;
            bool not_divied = true;
            for (auto y : pair) {
                if (y != '-' and y != '>' and y != ' ')
                    number += y;
                else if (y == '>') {
                    from = stoi(number);
                    number = "";
                }
            }
            to = stoi(number);
            cur_map[from].push_back(to);
            pair = "";
        }
    }
    return cur_map;
}

void find_cycle(int start_node, int cur_node, std::vector<int> visited) {
    if (start_node == cur_node and visited.size() > 0) {
        visited.push_back(cur_node);
        DISCOVERED_CYCLES.push_back(visited);
        return;
    }
    for (int visited_node : visited) {
        if (visited_node == cur_node) {
            return;
        }
    }

    visited.push_back(cur_node);
    for (int neighbour_node : MY_MAP[cur_node]) {
        find_cycle(start_node, neighbour_node, visited);
    }
}

std::string get_data(std::string filename) {
    std::ifstream file(filename);

    std::string fileContent = "";
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            fileContent += line; 
        }

        file.close();
    }
    else {
        std::cerr << "Error opening the file." << std::endl;
    }

    return fileContent;
}

void save_data(std::string outputFileName) {
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

int main(int argc, char* argv[]) {


    std::string inputFileName;
    std::string outputFileName;
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
    std::cout << edges;


    MY_MAP = adv_tokenizer(edges, "," , "->");


    //for (const auto& entry : d) {
    //    std::cout << "Node " << entry.first << " connects to: ";
    //    for (int connected_node : entry.second) {
    //        std::cout << connected_node << " ";
    //    }
    //    std::cout << std::endl;
    //}


    std::vector<int> visited;
    for (const auto& entry : MY_MAP) {
        find_cycle(entry.first, entry.first, visited);
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
    save_data(outputFileName);


    return 0;
}
