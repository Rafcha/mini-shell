#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void help() {
    cout << "aviable commands" << endl;
    cout << "help         : show help" << endl;
    cout << "exit         : quit" << endl;
    cout << "echo 'text'  : print text" << endl;
    cout << "cd 'dir'     : change directory" << endl;
    cout << "mkdir 'dir'  : create directory" << endl;
    cout << "rm 'file'    : remove file or directory" << endl;
    cout << "cat 'file'   : show file contents" << endl;
    cout << "ls 'dir'     : show files in directory" << endl;
    cout << "pwd          : present working directory" << endl;
}
void about() {
    cout << "--- Mini Shell ---" << endl;
    cout << "Version : 1.0" << endl;
    cout << "Author : Rafcha" << endl;
}
void pwd() {
    cout << fs::current_path() << endl;
}
void ls(const string& path) {
    fs::path target = path.empty() ? fs::current_path() : fs::path(path);

    if (!fs::exists(target)) {
        cout << "Path does not exist." << endl;
        return;
    }

    if (!fs::is_directory(target)) {
        cout << "Path is not a directory." << endl;
        return;
    }

    cout << "Files in: " << fs::absolute(target) << "\n\n";

    for (const auto& entry : fs::directory_iterator(target)) {
        string name = entry.path().filename().string();
        uintmax_t size = 0;

        if (entry.is_directory()) {
            cout << "\033[33m[DIR]  ";
        } else if (entry.is_regular_file()) {
            size = fs::file_size(entry.path());
            cout << "\033[34m[FILE] ";
        } else {
            cout << "\033[0m[????] ";
        }

        cout << name;

        if (entry.is_regular_file()) {
            cout << " (" << size << " B)";
        }

        cout << "\033[0m" << endl;
    }

    cout << endl;
}

void touch(const string& filename) {
    if (filename.empty()) {
        cout << "Error: No filename provided." << endl;
        return;
    }

    fs::path filepath = fs::absolute(filename);

    if (fs::exists(filepath)) {
        cout << "File already exists: " << filepath << endl;
        return;
    }

    ofstream file(filepath);
    if (!file) {
        cout << "Error: Could not create file." << endl;
    } else {
        cout << "Created: " << filepath << endl;
    }
}
void cd(const string& path) {
    if (path.empty()) {
        cout << "Error: no path provided." << endl;
        return;
    }

    fs::path target = fs::absolute(path);

    if (!fs::exists(target)) {
        cout << "Error: path does not exist." << endl;
        return;
    }

    if (!fs::is_directory(target)) {
        cout << "Error: not a directory." << endl;
        return;
    }

    fs::current_path(target);
    cout << "Directory changed to: " << fs::current_path() << endl;
}
void mkdir_(const string& dirname) {
    if (dirname.empty()) {
        cout << "Error: no folder name provided." << endl;
        return;
    }

    fs::path dir = fs::absolute(dirname);

    if (fs::exists(dir)) {
        cout << "Directory already exists." << endl;
        return;
    }

    if (fs::create_directory(dir)) {
        cout << "Created directory: " << dir << endl;
    } else {
        cout << "Failed to create directory." << endl;
    }
}
void rm(const string& target) {
    if (target.empty()) {
        cout << "Error: no target specified." << endl;
        return;
    }

    fs::path path = fs::absolute(target);

    if (!fs::exists(path)) {
        cout << "File or folder does not exist." << endl;
        return;
    }

    if (fs::is_directory(path)) {
        fs::remove_all(path);
        cout << "Deleted directory: " << path << endl;
    } else {
        fs::remove(path);
        cout << "Deleted file: " << path << endl;
    }
}
void cat(const string& filename) {
    if (filename.empty()) {
        cout << "Error: no file provided." << endl;
        return;
    }

    fs::path file = fs::absolute(filename);

    if (!fs::exists(file) || !fs::is_regular_file(file)) {
        cout << "File does not exist or is not a regular file." << endl;
        return;
    }

    ifstream in(file);
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
}
