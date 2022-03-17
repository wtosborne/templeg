#include <iostream>
#include "include/inja.hpp"
#include <string>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
using namespace inja;

int main(int argc, char * argv[]) {

    if(argc == 2 && strcmp(argv[1], "--help")==0) {
        cout << "USAGE: templeg [TEMPLATE]" << endl;
        cout << "To list templates, use templeg --list" << endl;
        return 0;
    }
    if(argc == 2 && strcmp(argv[1], "--list")==0) {
        string path = "./templates";
        for (const auto & entry : fs::directory_iterator(path)) {
            cout << entry.path().filename() << endl;
        }
        return 0;
    }
    
    Environment env;

    string filename = argv[1];

    json data = env.load_json("./templates/" + filename + ".json");

    for (auto& [key, value]: data.items()) {
        cout << "Field [" << key << "]:\n";
        string val;
        getline(cin, val);
        value = val;
    }

    Template temp = env.parse_template("./templates/" + filename + ".html");
    string result = env.render(temp, data);
    cout << result;



}