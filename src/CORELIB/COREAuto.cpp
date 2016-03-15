#include "COREAuto.h"

using namespace CORE;

ControlFlow WaitAction::call(void){
	if(timer.Get() == 0){
		timer.Start();
	}
	if(timer.Get()<=m_duration){
		return CONTINUE;
	}else{
		return END;
	}
}

void AutoControl::iter(){

	if(aqueue.empty() && !queueEmpty){
		outLog.appendLog("Auto Queue Empty");
		queueEmpty = true;
	}
	if(!aqueue.empty()){
	Action* a = aqueue.front();

	ControlFlow returnVal = a->call(position);

	switch(returnVal){
	case CONTINUE:
		break;
	case BACKGROUND:
		outLog.appendLog("Adding to Background:");
		outLog.appendLog(a->name);
		background.push_back(a);
		/* no break */
	case END:
		position++;
		aqueue.pop();
		if(!aqueue.empty()){
			a = aqueue.front();
			outLog.appendLog(a->name);
			a->init();
		}
		break;
	if(!background.empty()){
	std::vector<Action*>::iterator it = background.begin();
	while(it != background.end()){
		ControlFlow return_val = (*it)->call(position);
		if (return_val == END){
			it = background.erase(it);
		}else{
			++it;
		}
	}
	}
	}
	}
	/*
	std::vector<OrderAction*>::iterator it = actions.begin();
	for(it = actions.begin(); it != actions.end(); ++it){
//		cout << "tele init " << (*it)->name() << endl;
		(*it)->call();
	}
	*/



}


