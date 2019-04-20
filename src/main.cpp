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
        std::cout << "aberto" << "\n\n";
        for(std::string line; std::getline(xml, line);) {
            std::smatch results;
            std::cout << "parsing: " << line << std::endl; 
            while (regex_search(line, results, tag)) {
                if (!results.ready())
                    goto endrsearch; 
                if (results.str(0)[1] != '/') {
                    xmlstack.push(results.str(0));
                    std::cout << "opentag = " << results.str(0) << std::endl;
                } else {
                    auto closetag = results.str(0);
                    auto top = xmlstack.pop();
                    std::cout << "closetag = " << closetag << std::endl;
                    std::cout << "top = " << top << std::endl;
                    closetag.erase(1,1);
                    if (closetag != top)
                        throw std::out_of_range("unclosed tags!");
                }
                line = results.suffix().str();
        }
endrsearch: std::cout << "ended regsearch" << std::endl; 
        }
        if (!xmlstack.empty()) 
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
    std::cout << "parseou\n"; 

    return 0;
}
