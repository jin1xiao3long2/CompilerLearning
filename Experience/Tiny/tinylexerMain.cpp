//
// Created by XM on 2021/3/24.
//

#include <Tiny_Lexer.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class lineInfo final : public tn::token_base {

    std::string info;
public:
    lineInfo(int l, int c, std::string info) : tn::token_base(l, c), info(info) {}

    ~lineInfo() = default;

    std::string get_string() const override {
        return info;
    }

    tn::token_type get_type() const override {
        return tn::token_type::null_type;
    }

};

int get_info(std::string &sp, const std::string &filename, std::vector<tn::token_base *> &lineinfo) {
    std::fstream fs;
    fs.open(filename, std::ios::in);
    bool newline = false;
    int l = 0;
    while (!fs.eof()) {
        std::string s;
        std::getline(fs, s);
        l++;
        lineinfo.push_back(new lineInfo(l, 0, s));
        if (newline)
            s = '\n' + s;
        newline = true;
        sp += s;
    }
//    std::cout << l << std::endl;
    if (lineinfo.back()->get_string().empty())
        lineinfo.pop_back();
    lineinfo.push_back(new lineInfo(l, 0, "EOF"));
    return l;
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
    write_filename = prefix + ".txt";
}

void write_syntax_tree(const std::deque<tn::token_base *> &tokens, const std::string &write_filename) {
    std::fstream fs;
    fs.open(write_filename, std::ios::out);
    for (auto iter = tokens.begin(); iter != tokens.end(); iter++) {
        if ((*iter)->get_type() != tn::token_type::null_type)
            fs << '\t';
        else {
            if ((*iter)->get_string().empty()) {
                continue;
            }
        }
        fs << (*iter)->get_line() << ": " << (*iter)->get_show_info() << std::endl;
    }
}

int main(int argc, char **argv) {
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
    std::vector<tn::token_base *> lineinfo;
    int line = get_info(sp, filename, lineinfo);
//get text info

//    std::cout << sp;
    tn::Lexer *lexer = new tn::Lexer(sp);
    lexer->Lex();
    std::deque<tn::token_base *> tokens = lexer->getTokens();
//    get tokens


    std::deque<tn::token_base *> show_tokens;
    int j = 0;
    for (int i = 1; i < line + 1; i++) {
        show_tokens.push_back(lineinfo.at(i - 1));
//        std::cout << i << ": " << lineinfo.at(i - 1)->get_string() << std::endl;
        for (j; j < tokens.size();) {
            if (tokens.at(j)->get_line() == i) {
                show_tokens.push_back(tokens.at(j));
                j++;
            } else {
                break;
            }
        }
    }
    if (lineinfo.size() == line + 1) {
        show_tokens.push_back(lineinfo.at(line));
    }

//   put tokens in order

//    for (auto iter = show_tokens.begin(); iter != show_tokens.end(); iter++) {
//        if (!((*iter)->get_type() == tn::token_type::null_type))
//            std::cout << "\t";
//        else {
//            if((*iter)->get_string().empty()){
//                continue;
//            }
//        }
//        std::cout << (*iter)->get_line() << ": " << (*iter)->get_show_info() << std::endl;
//    }

    std::string writeFilename;
    get_write_filename(filename, writeFilename);
//write into files
    write_syntax_tree(show_tokens, writeFilename);

    return 0;
}