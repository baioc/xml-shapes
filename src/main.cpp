//! Copyright [2019] <Alek Frohlich, Gabriel Sant'Anna>

/* libraries */
#include <iostream>
#include <fstream>
#include <regex>

/* our includes */
#include "linked_stack.cpp"

void parsexml(const char * filename) {
    structures::LinkedStack<std::string> xmlstack;
    std::regex tag("<[^>]*>");
    std::ifstream xml;
    xml.open(filename);
    if (xml.is_open()) {
        std::cout << "aberto" << std::endl;
        for(std::string line; std::getline(xml, line);) {
            std::smatch results;
            while (regex_search(line, results, tag)) {
                if (!results.ready())
                    goto endrsearch; 
                if (results.str(1)[2] != '/') {
                    xmlstack.push(results.str(1));
                } else {
                    if (results.str(1) != xmlstack.pop())
                        throw std::out_of_range("unclosed tags!");
                }
                line = results.suffix().str();
        }
endrsearch: std::cout << "ended regsearch" << std::endl; 
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
