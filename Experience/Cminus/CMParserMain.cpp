//
// Created by XM on 2021/3/29.
//

#include <CM_Parser.hpp>
#include <CM_Lexer.hpp>
#include <iostream>
#include <fstream>
#include <vector>

void get_info(std::string &str, const std::string &filename) {
    std::fstream fs;
    fs.open(filename, std::ios::in);
    bool newline = false;
    if(fs.fail()){
        std::cerr << "file open failed, please check parameters";
        exit(-1);
    }
    while (!fs.eof()) {
        std::string s;
        std::getline(fs, s);
        if (newline)
            s = '\n' + s;
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
        prefix = filename.substr(n, filename.find('.'));
    else
        prefix = filename.substr(0, filename.find('.'));
    write_filename = prefix + "_build_tree" + ".txt";
}

void write_syntax_tree(const std::deque<std::string> *messages, const std::string &write_filename) {
    std::fstream fs;
    fs.open(write_filename, std::ios::out);
    if(fs.is_open()) {
        for (auto iter = messages->begin(); iter != messages->end(); iter++) {
            fs << iter->data() << '\n';
        }
    }else{
        std::cerr << "can't open file" << std::endl;
    }
}

int main(int argc, char **argv) {

    //parse arguments
    if (argc != 2) {
        std::cerr << "wrong parameters" << std::endl;
        exit(-1);
    }

    std::string filename = argv[1];
    if (!check_suffix(filename, "c-")) {
        std::cerr << "Unknown file type, please check the input" << std::endl;
        exit(-1);
    }

    std::string sp;
    get_info(sp, filename);
//    std::cout << sp;

    //lex
    cm::Lexer *lexer = new cm::Lexer(sp);
    lexer->Lex();
    std::deque<cm::token_base *> tokens = lexer->getTokens();

//    test tokens
//    for(auto iter = tokens.begin(); iter != tokens.end(); iter++){
//        std::cout << "line : " << (*iter)->get_line()  << "  column : " << (*iter)->get_column() << " info :  " << (*iter)->get_show_info() << std::endl;
//    }

//    parse
    cm::Parser *parser = new cm::Parser(tokens);
    parser->parse();


    //get string
    std::deque<std::string>* mes = parser->getMessages();

//    test syntax tree
//    for(auto iter = mes->begin(); iter != mes->end(); iter++){
//        std::cout << iter->data() << std::endl;
//    }
    //write into files
    std::string writeFilename;
    get_write_filename(filename, writeFilename);
    write_syntax_tree(mes, writeFilename);
//    std::cout << "filename is " << writeFilename << std::endl;
    return 0;
}

