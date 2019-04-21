//! Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>

/* libraries */
#include <fstream>
#include <iostream>
#include <regex>

/* our includes */
#include "linked_stack.cpp" // include de .cpp


void parsexml(const char * filename) {
    structures::LinkedStack<std::string> xmlstack;
    std::regex tag("<[^>]*>");

    std::ifstream xml;
    xml.open(filename);
    if (!xml.is_open()) {
		std::cout << "fechado" << '\n';
		return;
	}

	std::cout << "aberto" << "\n\n";

	for (std::string line; std::getline(xml, line);) {
		std::smatch results;

		std::cout << "parsing: " << line << '\n';
		while (regex_search(line, results, tag)) {
			if (!results.ready())
				break;

			if (results.str(0)[1] != '/') {
				xmlstack.push(results.str(0));
				std::cout << "opentag = " << results.str(0) << '\n';
			} else {
				auto closetag = results.str(0);
				std::cout << "closetag = " << closetag << '\n';

				const auto top = xmlstack.pop();
				std::cout << "top = " << top << '\n';

				closetag.erase(1,1);
				if (closetag != top)
					throw std::out_of_range("unclosed tags!"); // out_of_range ?
			}

			line = results.suffix().str();
		}

		std::cout << "ended regsearch" << '\n';
	}

	if (!xmlstack.empty())
		throw std::out_of_range("unclosed tags!");

    xml.close();
}


int main() {
    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    parsexml(xmlfilename);
    std::cout << "parseou\n";

    return 0;
}
