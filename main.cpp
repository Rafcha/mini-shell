#include <iostream>
#include <string>
#include <filesystem>
#include "modules/commands.hpp"

using namespace std;
namespace fs = std::filesystem;

int main() {
    cout << "--- Mini Shell ---" << endl;
    while (true)
    {
        string command;
        cout << "$ ";
        getline(cin, command);
        if (command == "help") {
            help();
        } 
        else if (command == "" || command == " ") {
            cout;
        }
        else if (command.rfind("echo ", 0) == 0) {
            cout << command.substr(5) << endl;
        }
        else if (command == "exit") {
            break;
        }
        else if (command == "about") {
            about();
        }
        else if (command == "pwd") {
            pwd();
        }
        else if (command.rfind("ls", 0) == 0) {
            string path = command.length() > 3 ? command.substr(3) : "";
            ls(path);
        } else if (command.rfind("touch ", 0) == 0) {
            string filename = command.substr(6);
            touch(filename);
        } else if (command.rfind("cd ", 0) == 0) {
            cd(command.substr(3));
        } else if (command.rfind("mkdir ", 0) == 0) {
            mkdir_(command.substr(6));
        } else if (command.rfind("rm ", 0) == 0) {
            rm(command.substr(3));
        } else if (command.rfind("cat ", 0) == 0) {
            cat(command.substr(4));
        }

        else {
            cout << "unknown command" << endl;
        }
    }
    
}