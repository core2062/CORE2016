
#ifndef COREAUTO_H
#define COREAUTO_H

#include <vector>
#include <string>
#include <queue>
//#include "CORERobot.h"
#include "ActionTypes.h"

namespace CORE{

enum ControlFlow{
	CONTINUE,
	END,
	BACKGROUND
};



class AutoControl{
//	CORERobot& robot;
	std::queue<OrderAction*> aqueue;
	std::vector<Action*> background;
	bool queueEmpty = false;
	int position = 1;

public:

	AutoControl(/*CORERobot& robot*/)
//		robot(robot)
		{};

	void iter (void);
	void init(void){
		aqueue.front()->init();
	}
	void add (OrderAction& a){
		aqueue.push(&a);
	}
	void add (OrderAction* a){
		aqueue.push(a);
	}
	void add (ConditionAction& a){
		background.push_back(&a);
	}
	void add (ConditionAction* a){
		background.push_back(a);
	}

};

}





#endif
