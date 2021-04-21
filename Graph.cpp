#include "GraphNode.h"
#include "NodeRelation.h"
#include "Graph.h"
#include "vector"
#include "iostream"

// Private -----------------------------------

GraphNode* Graph::getNode(NodeValue value){
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i]->getValue() == value){
			return nodes[i];
		}
	}
	return nullptr;
}

std::vector<NodeRelation*> Graph::tryNextStep(std::vector<NodeRelation*> previousPath, GraphNode* currentStep){
  std::vector<NodeRelation*> relations = currentStep->getRelations();
  std::vector<NodeRelation*> biggestPath = currentStep->getRelations();

  for(auto i = relations.begin(); i != relations.end(); i++){
    if((*i)->notIn(previousPath)){
      std::vector<NodeRelation*> path = previousPath;
      path.push_back(*i);

      std::vector<NodeRelation*> pathResult = tryNextStep(path, (*i)->getOtherNode(currentStep));
      if(pathResult.size() == numberOfRelations()){
        return pathResult;
      }
    }
  }
  return previousPath;
}

// Public -----------------------------------

std::vector<NodeRelation*> Graph::tryToFindEulerianPath(){
  std::vector<NodeRelation*> result;
  std::vector<NodeRelation*> emptyVector;
  for(auto i = nodes.begin(); i != nodes.end(); i++){
    result = tryNextStep(result, (*i));
  }

  if(result.size() == numberOfRelations()){
    return result;
  }
  else {
    return emptyVector;
  }
}

std::vector<NodeRelation*> Graph::findBiggestPath(){
  std::vector<NodeRelation*> result;
  std::vector<NodeRelation*> emptyVector;
  for(auto i = nodes.begin(); i != nodes.end(); i++){
    result = tryNextStep(result, (*i));
  }
  return result;
}

NodeValue Graph::createNode(NodeValue value){
	GraphNode* result = getNode(value);
	if(result == nullptr){
		nodes.push_back(new GraphNode(value));
		return nodes.back()->getValue();	
	}
	else{
		return result->getValue();
	}
}

void Graph::removeNode(NodeValue value){
	for(auto i = nodes.begin(); i != nodes.end(); i++){
		if((*i)->getValue() == value){
			delete(*i);
			nodes.erase(i);
			break;
		}
	}
}

void Graph::createRelation(NodeValue valueOne, NodeValue valueTwo){
	GraphNode* nodeOne = getNode(valueOne);
	GraphNode* nodeTwo = getNode(valueTwo);
	
	nodeOne->addRelation(nodeTwo);
}
	
void Graph::removeRelation(NodeValue valueOne, NodeValue valueTwo){
	GraphNode* nodeOne = getNode(valueOne);
	GraphNode* nodeTwo = getNode(valueTwo);
  NodeRelation* relation = nodeOne->getRelationWith(nodeTwo->getValue());
	
	nodeOne->endRelation(relation);
}

bool Graph::isEulerian(){
	for(auto i = nodes.begin(); i!= nodes.end(); i++){
		int relationsSize = (*i)->getRelations().size();
		if(relationsSize % 2 != 0 || relationsSize == 0){
			return false;
		}
	}
	return true;
}

bool Graph::isSemiEulerian(){
	int oddRelationsCount = 0;
	for(auto i = nodes.begin(); i!= nodes.end(); i++){
		int relationsSize = (*i)->getRelations().size();
		if(relationsSize % 2 != 0){
			oddRelationsCount++;
		}
		if(relationsSize == 0 || oddRelationsCount > 2){
			return false;
		}
	}
	return oddRelationsCount == 2;
}

int Graph::numberOfRelations(){
  std::vector<NodeRelation*> allRelations;
  for(auto node = nodes.begin(); node != nodes.end(); node++){
    std::vector<NodeRelation*> relations = (*node)->getRelations();
    for(auto relation = relations.begin(); relation != relations.end(); relation++){
      if((*relation)->notIn(allRelations)){
        allRelations.push_back(*relation);
      }
    }
  }
  return allRelations.size();
}

void Graph::printNodes(){
	std::cout << "Nodes:";
	for(int i = 0; i < nodes.size(); i++){
		std::cout << " " << nodes[i]->getValue();
	}
	std::cout << "\n\n";
}

void Graph::printRelations(){
	for(int i = 0; i < nodes.size(); i++){
		GraphNode* currentNode = nodes[i];
		std::cout << "Node: " << currentNode->getValue() << "\n";
		std::vector<NodeRelation*> relations = currentNode->getRelations();
		
		for(auto i = relations.begin(); i != relations.end(); i++){
			std::cout << "Relation: " << (*i)->retrieveNodeOneValue() << " <-> " << (*i)->retrieveNodeTwoValue() << "\n"; 
		}
		std::cout << "\n";
	}
}

void Graph::printStatus(){
	if(isEulerian()){
		std::cout << "Is eulerian\n";
	}
	else if(isSemiEulerian()){
		std::cout << "Is semi eulerian\n";
	}
	else{
		std::cout << "Is not eulerian\n";
	}
}

void Graph::printPath(std::vector<NodeRelation*> path){
  std::cout << "Path:";
  for(auto i = path.begin(); i != path.end(); i++){
    std::cout << " -> "<< (*i)->retrieveNodeOneValue() << " <-> "  << (*i)->retrieveNodeTwoValue();
  }
  std::cout << "\n\n";
}


























