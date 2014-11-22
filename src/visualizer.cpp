
#include "visualizer.h"

void Visualizer::checkCurrController(std::string newControllerName)
{

    Agnode_t* n;
    for (n = agfstnode(graph); n; n = agnxtnode(graph, n))
    {
        if (newControllerName.compare(ND_label(n)->text) == 0)
        {
            setCurrController(newControllerName);
        }
    }
}

void Visualizer::createGraph(std::map<std::string, Controller>& scripts)
{
    /*
    graph = agopen("Visualizer", Agdirected, 0);

    for (auto it = scripts.begin(); it != scripts.end(); it++)
    {
        std::cout << it->second.getName() << std::endl;
    }


//    Agedge_t* edge1 = agedge(graph, nodes.at(0)->gvNode, nodes.at(1)->gvNode, "edgeone", 1);
//    */
}

int Visualizer::createLayout()
{
    if (graph == NULL)
    {
        std::cerr << "Error: Graph not initialized" << std::endl;
        return -1;
    }
    gvLayout(context, graph, "dot");

    std::cout << "BB: " << GD_bb(graph).LL.x << ", " << GD_bb(graph).LL.y << " -> " << 
        GD_bb(graph).UR.x << ", " << GD_bb(graph).UR.y << std::endl;

    return 0;
}

int Visualizer::openGraph(std::string filename)
{

    FILE* file;

    file = fopen(filename.c_str(), "r");

    graph = agread(file, 0);

    if (graph == NULL)
    {
        std::cerr << "Error reading in graph file " << filename << std::endl;
        return -1;
    }

    Agnode_t* n;
    for (n = agfstnode(graph); n; n = agnxtnode(graph, n))
    {
        nodes.push_back(new Node(n));
    }
    n = NULL;
    return 0;

}

void Visualizer::printAllNodes()
{
    Agnode_t* n;
    for (n = agfstnode(graph); n; n = agnxtnode(graph, n))
    {
        //std::cout << (ND_label(n)) << std::endl;
        //
        std::cout << ND_label(n)->text << std::endl;
        std::cout << ND_coord(n).x << ", " << ND_coord(n).y << std::endl;
    }

}
