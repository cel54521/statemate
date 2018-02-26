/**
 * @file parser.c
 * @brief statemateç\ï∂âêÕäÌ
 * @author cel54521
 */
#include "parser.h"
#include "keyword.h"
#include <stdlib.h>

Parser::Parser(FILE *in, FILE *out){
  this->lineNo = 0;
  this->in = in;
  this->out = out;
}

bool Parser::getPhrase(void){
  char type[64];
  char buf[10340];

  if(fgets(buf,10240,in) != NULL){
    this->lineNo++;
    sscanf(buf,"%[^,],%s\n",type,phrase.buf);

    fprintf(stderr,"%s,%d\n",phrase.buf,phrase.type);

    if(strcmp(type,"ENTRY") == 0){
      phrase.type = ENTRY;
    }else if(strcmp(type,"DO") == 0){
      phrase.type = DO;
    }else if(strcmp(type,"EXIT") == 0){
      phrase.type = EXIT;
    }else if(strcmp(type,"TOKEN") == 0){
      phrase.type = TOKEN;
    }else if(strcmp(type,"R_PAR") == 0){
      phrase.type = R_PAR;
    }else if(strcmp(type,"L_PAR") == 0){
      phrase.type = L_PAR;
    }else if(strcmp(type,"ALLOW") == 0){
      phrase.type = ALLOW;
    }else if(strcmp(type,"R_BRACKET") == 0){
      phrase.type = R_BRACKET;
    }else if(strcmp(type,"L_BRACKET") == 0){
      phrase.type = L_BRACKET;
    }else if(strcmp(type,"ENTRY_DO_EXIT_BLOCK") == 0){
      phrase.type = ENTRY_DO_EXIT_BLOCK;
    }else if(strcmp(type,"EXPRESSION") == 0){
      phrase.type = EXPRESSION;
    }else{
      phrase.type == UNKNOWN;
      return false;
    }
  }else{
    return false;
  }

  return true;
}

void Parser::analyze(EventList* const event, StateList* const state){
  char buf[10240];
  Event eventTmp;
  State stateTmp;
  Trigger *triggerTmp;
  std::vector<Trigger*>::iterator itr;

  while(getPhrase() == true){
    if(this->phrase.type == TOKEN){
      strcpy(buf, this->phrase.buf);

      getPhrase();
      if(this->phrase.type == EXPRESSION){
        // <event>
        strcpy(eventTmp.eventName, buf);
        strcpy(eventTmp.condition, this->phrase.buf);

        event->push(eventTmp);
      }else if(this->phrase.type == L_PAR){
        // <state>

        // entry
        getPhrase();
        if(this->phrase.type == ENTRY){
          getPhrase();
          if(this->phrase.type == ENTRY_DO_EXIT_BLOCK){
            strcpy(stateTmp.stateName, buf);
            strcpy(stateTmp.entryBlock, this->phrase.buf);
          }else{
            fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
            return;
          }
        }else{
          fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
          return;
        }

        // do
        getPhrase();
        if(this->phrase.type == DO){
          getPhrase();
          if(this->phrase.type == ENTRY_DO_EXIT_BLOCK){
            strcpy(stateTmp.stateName, buf);
            strcpy(stateTmp.doBlock, this->phrase.buf);
          }else{
            fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
            return;
          }
        }else{
          fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
          return;
        }

        // exit
        getPhrase();
        if(this->phrase.type == EXIT){
          getPhrase();
          if(this->phrase.type == ENTRY_DO_EXIT_BLOCK){
            strcpy(stateTmp.stateName, buf);
            strcpy(stateTmp.exitBlock, this->phrase.buf);
          }else{
            fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
            return;
          }
        }else{
          fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
          return;
        }

        // trigger-list
        while(getPhrase() == true){
          if(this->phrase.type == TOKEN){
            getPhrase();
            if(this->phrase.type == ALLOW){
              getPhrase();
              if(this->phrase.type == TOKEN){
                triggerTmp = (Trigger*)malloc(sizeof(Trigger));
                strcpy(triggerTmp->triggerName, buf);
                strcpy(triggerTmp->nextState, this->phrase.buf);

                stateTmp.trigger_list.push_back(triggerTmp);
              }else{
                fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
                return;
              }
            }else{
              fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
              return;
            }
          }else{
            // state-end
            if(this->phrase.type == R_PAR){

            }else{
              fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
              return;
            }

            break;
          }
        }

        state->push(stateTmp);

        // triggerTmpäJï˙
        for(itr = stateTmp.trigger_list.begin(); itr < stateTmp.trigger_list.end(); itr++){
          free(*itr);
        }
      }else{
        // error
        fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
        return;
      }
    }
  }
}
