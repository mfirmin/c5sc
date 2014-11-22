#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <vector>
#include <utility>
#include <string>

/* ------
 * Point of this class is to be able to store a snapshot of a given controller at some time.
 * whether it is the current controller, or information about when to transfer. etc etc
 */

class Hierarchy
{

    public:

        bool isEqual(Hierarchy* other);

        void push(std::string s, int i) { data.push_back(std::pair<std::string, int>(s,i)); }

        void pop() { data.pop_back(); }

        void setLastPhase(int p) { data.back().second = p; }

        int depth() { return data.size(); }

        void print();

        std::vector<std::pair<std::string, int> >::iterator end() { return data.end(); }
        std::vector<std::pair<std::string, int> >::iterator begin() { return data.begin(); }


    private:
        std::vector<std::pair<std::string, int> > data; // controller-phase hierarchical structure.


};

#endif // HIERARCHY_H
