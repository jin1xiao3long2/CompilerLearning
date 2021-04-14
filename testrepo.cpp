//
// Created by XM on 2021/3/29.
//

#include <iostream>
#include <fstream>

void get_info(std::string &str, const std::string &filename) {
    std::fstream fs;
    fs.open(filename, std::ios::in);
    bool newline = false;
    while (!fs.eof()) {
        std::string s;
        std::getline(fs, s);
        if (newline)
            s = "\n" + s;
        newline = true;
        str += s;
    }
}

bool check_suffix(const std::string &filename, std::string suffix) {
    int n = filename.rfind('.');
    if (filename.substr(n + 1, filename.size() - 1) != suffix)
        return false;
    return true;
}

void get_write_filename(const std::string &filename, std::string &write_filename) {
    int n = filename.find('\\');
    std::string prefix;
    if (n != std::string::npos)
        prefix = filename.substr(n, filename.rfind('.'));
    else
        prefix = filename.substr(0, filename.find('.'));
    write_filename = prefix + "_build_tree" + ".txt";
}


int main(int argc, char **argv) {

    //parse arguments
    if (argc != 2) {
        std::cerr << "wrong parameters" << std::endl;
        exit(-1);
    }

    std::string filename = argv[1];
    if (!check_suffix(filename, "tny")) {
        std::cerr << "Unknown file type, please check the input" << std::endl;
        exit(-1);
    }

    std::string sp;
    get_info(sp, filename);
    std::cout << sp;



    std::string writeFilename;
    get_write_filename(filename, writeFilename);
//    write_syntax_tree(mes, writeFilename);
    std::cout << "filename is " << writeFilename << std::endl;
    return 0;
}

