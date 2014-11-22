#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <string>
#include <vector>
#include <map>
#include "controller.h"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include "VECTOR.h"



struct Node
{
    Node( Agnode_t* n ) { ptr = n; }

    Agnode_t* ptr;

    char* getLabel() { return ND_label(ptr)->text; }

    VECTOR getPos() { return VECTOR(ND_coord(ptr).x, ND_coord(ptr).y, 0); }
};

class Visualizer
{

    public:
        Visualizer() { context = gvContext(); currController = "";}

        void createGraph( std::map<std::string, Controller>& scripts );
        int openGraph( std::string filename );
        int createLayout();

        void printAllNodes();


        std::vector<Node*>& getNodes() { return nodes; }
        
        VECTOR getBB() { return VECTOR(GD_bb(graph).UR.x, GD_bb(graph).UR.y, 0); }


        void setCurrController(std::string s) { currController = s; }
        std::string getCurrController() { return currController; }

        void checkCurrController(std::string);

        Agraph_t* getGraphPtr() { return graph; }

    private:
        Agraph_t* graph;
        GVC_t* context;

        std::vector<Node*> nodes;
        std::string currController;
};



#endif // VISUALIZER_H
