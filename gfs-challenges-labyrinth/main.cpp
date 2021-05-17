#include "iostream"
#include "string"
#include "Graph.h"
#include "Node.h"
#include "utils.h"
#include "Labyrinth.h"
#include "Position.h"

int main(int filesCount, char** file){

    std::cout << "Insert labyrinth file name without .txt extension:\n";
    std::string fileName;
    std::cin >> fileName;
//----
    std::cout << "Reading and creating graph...\n";
    Labyrinth lab = Labyrinth();
    Graph result = lab.transformIntoGraphFromFile(fileName);

    Node* entrance = result.getNode(lab.retrieveStartPosition(fileName));
    Node* exit = result.getNode(lab.retrieveEndPosition(fileName));

    std::vector<std::string> resultFileContent;

//----
    std::cout << "Executing depth search...\n";

    resultFileContent.push_back("Depth search result: \n\n");
    std::vector<Value> depthSearchResult = result.depthSearch(entrance, exit);
    std::cout << "Depth search size: " << depthSearchResult.size() << "\n\n";

    resultFileContent = joinVectors(resultFileContent, getPathInfo(depthSearchResult));
//----
    std::cout << "Executing width search...\n";

    resultFileContent.push_back("Width search result: \n\n");
    std::vector<Value> widthSearchResult = result.widthSearch(entrance, exit);
    std::cout << "Width search size: " << widthSearchResult.size() << "\n\n";

    resultFileContent = joinVectors(resultFileContent, getPathInfo(widthSearchResult));

    resultFileContent.push_back(lab.retrieveResolvedLabyrinthString(fileName, widthSearchResult));
//----

    std::string outputFileName = fileName + "-output";
    std::cout << "Result stored in " << outputFileName << " file!\n";
    makeFile(outputFileName, resultFileContent);

    return 1;
}
