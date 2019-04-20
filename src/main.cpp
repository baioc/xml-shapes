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
        std::stringstream ss;
        for(std::string line; std::getline(xml, line);) {
            for (auto it = line.begin(); it < line.end(); it++) {
            /* o string::iterator it tem o valor de cada char, *it pra acessa-lo

            Logica de parsing do que esta sendo lido aqui...

            */
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
