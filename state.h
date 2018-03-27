/**
 * @file state.h
 * @brief state
 * @author cel54521
 */
#ifndef _STATE_
#define _STATE_

#include <vector>

typedef struct _Trigger{
  char triggerName[10240];
  char nextState[10240];
} Trigger;

typedef struct _State{
  char stateName[10240];
  char entryBlock[10240];
  char doBlock[10240];
  char exitBlock[10240];
  std::vector<Trigger*> trigger_list;

} State;

class StateList{
 private:
  std::vector<State> stateList;
 public:
   StateList(void);
  ~StateList(void);

  State* newState(void);
  Trigger* newTrigger(void);

  void print(void);
};

#endif
