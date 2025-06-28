#pragma once
void help();
void about();
void pwd();
void ls(const std::string& path = "");
void touch(const std::string& filename);
void cd(const std::string& path);
void mkdir_(const std::string& dirname);
void rm(const std::string& target);
void cat(const std::string& filename);
