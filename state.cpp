/**
 * @file state.cpp
 * @brief state
 * @author cel54521
 */
#include "state.h"
#include <stdlib.h>
#include <string.h>

StateList::StateList(void){

}

StateList::~StateList(void){
  for(itr = stateList.begin(); itr < stateList.end(); itr++){
    free(&(*itr));
  }
}

void StateList::push(State state){
  std::vector<Trigger>::iterator itr;

  State *tmp = (State*)malloc(sizeof(State));

  strcpy(state.stateName, tmp->stateName);
  strcpy(state.entryBlock, tmp->entryBlock);
  strcpy(state.doBlock, tmp->doBlock);
  strcpy(state.exitBlock, tmp->exitBlock);

  for(itr = state.trigger_list.begin(); itr < state.trigger_list.end(); itr++){
    Trigger *tmpTrigger;
    tmpTrigger = (Trigger*)malloc(sizeof(Trigger));

    tmpTrigger = *itr;
    tmp->trigger_list.push_back(tmpTrigger);
  }

  this->stateList.push_back(*tmp);
}

#ifdef __DEBUG__
void StateList::print(void){
  std::vector<State>::iterator itr;

  for(itr = stateList.begin(); itr < stateList.end(); itr++){
    fprintf(stderr, "%s,%s\n", itr->stateName, itr->condition);
  }
}
#endif
