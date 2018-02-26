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
  std::vector<Trigger*>::iterator itrTrigger;
  std::vector<State>::iterator itrStateList;

  for(itrStateList = this->stateList.begin(); itrStateList < this->stateList.end(); itrStateList++){

    for(itrTrigger = itrStateList->trigger_list.begin(); itrTrigger < itrStateList->trigger_list.end(); itrTrigger++){
      free(*itrTrigger);
    }

    free(&(*itrStateList));
  }

}

void StateList::push(State state){
  std::vector<Trigger*>::iterator itr;

  State *tmp = (State*)malloc(sizeof(State));

  strcpy(tmp->stateName, state.stateName);
  strcpy(tmp->entryBlock, state.entryBlock);
  strcpy(tmp->doBlock, state.doBlock);
  strcpy(tmp->exitBlock, state.exitBlock);

  for(itr = state.trigger_list.begin(); itr < state.trigger_list.end(); itr++){
    Trigger *tmpTrigger;
    tmpTrigger = (Trigger*)malloc(sizeof(Trigger));

    strcpy(tmpTrigger->triggerName, (*itr)->triggerName);
    strcpy(tmpTrigger->nextState, (*itr)->nextState);

    tmp->trigger_list.push_back(tmpTrigger);
  }

  this->stateList.push_back(*tmp);
}

void StateList::print(void){
  std::vector<State>::iterator itr;

  for(itr = stateList.begin(); itr < stateList.end(); itr++){
    fprintf(stderr, "%s,%s\n", itr->stateName, itr->entryBlock, itr->doBlock, itr->exitBlock);
  }
}
