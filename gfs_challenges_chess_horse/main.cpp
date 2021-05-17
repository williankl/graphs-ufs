#include "iostream"
#include "string"
#include "Graph.h"
#include "Node.h"
#include "utils.h"
#include "ChessHorseHandler.h"

int main(int filesCount, char** file){

    ChessHorseHandler handler;

    std::cout << "Building graph to represent the horse movements...\n";
    Graph g = handler.getHorsePath();

    std::string outputName = "output";
    std::vector<std::string> results;

    results.push_back("Created nodes:\n");
    results = joinVectors(results, getNodesInfo(g.getNodes()));

    std::cout << "Finding Hamiltonian path...\n";
    results.push_back("Hamiltonian path:\n");
    results = joinVectors(results, getPathInfo(g.findHamiltonianPath()));

    makeFile(outputName, results);
    std::cout << "Saved result at " << outputName << ".txt file.\n\n";
    return 1;
}
