//! Copyright [2019] <Alek Frohlich, Gabriel Sant'Anna>

/* libraries */
#include <iostream>
#include <fstream>
#include <sstream>

/* our includes */
#include "linked_stack.cpp"

void parsexml(const char * filename) {
    structures::LinkedStack<std::string> xmlstack;
    std::ifstream xml;
    xml.open(filename);
    if (xml.is_open()) {
        std::cout << "aberto" << std::endl;
        bool inside = false;
        bool opentag = false;
        std::stringstream ss;
        for(std::string line; std::getline(xml, line);) {
            for (auto it = line.begin(); it < line.end(); it++) {
                auto ch = *it;
                if (!inside && ch == '<') {
                    inside = true;
                    opentag = true;
                }   
                if (inside && ch == '/') {
                    opentag = false;
                }
                if (inside && ch == '>' && opentag) {
                    inside = false;
                    opentag = false;
                    xmlstack.push(ss.str());
                    std::stringstream().swap(ss);
                }
                if (inside && ch == '>' && !opentag) {
                    inside = false;
                        if (xmlstack.pop() != ss.str())
                            throw std::out_of_range("unclosed tags!");
                }
                if (inside && ch == '/') {
                } else if (inside) {
                    ss << ch;
                }
            }
        }
        if (xmlstack.empty()) 
            throw std::out_of_range("unclosed tags!");
    } else {
        std::cout << "fechado" << std::endl;
    }
    xml.close();
}


int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    parsexml(xmlfilename); 
    std::cout << "parseou"; 

    return 0;
}
