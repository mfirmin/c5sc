#ifndef ENVACTION_H
#define ENVACTION_H

#include <string>
#include <stdio.h>
#include <vector>

#include "action.h"

void toggleVisible(std::string s);
void toggleCollidable(std::string s);

class EnvAction : public Action
{

	public:

        EnvAction() { done = false; }

		virtual void performAction();
		virtual void reset() { done = true; }
        virtual void setOptimizable(std::vector<Value*>&) { return; }
        bool writeToFile(std::ofstream& ofs) { ofs << "NO SUPPORT FOR ENV ACTIONS YET\n"; return false; }

        std::vector<std::function<void()> > actions;

    private:

        bool done;


};

#endif // ENVACTION_H
