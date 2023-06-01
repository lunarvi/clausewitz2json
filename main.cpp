#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Node.h"
#include "Lexer.h"
#include "Parser.h"

int main() {
    std::ifstream t("c:\\Users\\jarvi\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\lubeck.eu4");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string input = buffer.str();
    int index = input.find("EU4txt");
    if (index != -1) {
        input.erase(0, 6);
    }
    Lexer lexer('{' + input + '}');


    Parser parser(lexer);

    std::unique_ptr<Node> ast = parser.parse();
    std::cout << "Done! " << std::endl;
    std::string json = ast->toJSON();
    std::ofstream wf("student.dat", std::ios::out);
    wf << json;
    wf.close();
    std::cout << json.length() << std::endl;

    return 0;
}