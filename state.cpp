/**
 * @file state.cpp
 * @brief state
 * @author cel54521
 */
#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StateList::StateList(void){

}

StateList::~StateList(void){

}


State* StateList::newState(void){
  State *tmp = (State*)malloc(sizeof(State));

  // ‰Šú‰»
  strcpy(tmp->stateName, "");
  strcpy(tmp->entryBlock, "");
  strcpy(tmp->doBlock, "");
  strcpy(tmp->exitBlock, "");

  this->stateList.push_back(tmp);

  return tmp;
}

Trigger* StateList::newTrigger(void){
  std::vector<Trigger*>::iterator itr;
  std::vector<State*>::iterator stateItr;
  Trigger *tmpTrigger;


  tmpTrigger = (Trigger*)malloc(sizeof(Trigger));

  strcpy(tmpTrigger->triggerName, "");
  strcpy(tmpTrigger->nextState, "");

  stateItr = stateList.end()-1;

  (*stateItr)->trigger_list.push_back(tmpTrigger);

  return tmpTrigger;
}


void StateList::print(void){
  std::vector<State*>::iterator itr;

  fprintf(stderr,"State\n");
  for(itr = stateList.begin(); itr < stateList.end(); itr++){
    fprintf(stderr, "%s,%s,%s,%s\n", (*itr)->stateName, (*itr)->entryBlock, (*itr)->doBlock, (*itr)->exitBlock);
  }
}
