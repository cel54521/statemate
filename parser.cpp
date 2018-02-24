/**
 * @file parser.c
 * @brief statemate\•¶‰ðÍŠí
 * @author cel54521
 */
#include "parser.h"
#include "keyword.h"

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
    sscanf(buf,"%[^,],%[^,]",type,phrase.buf);

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

void Parser::analyze(Event* const event, State* const state){
  char buf[10240];
  Event eventTmp;
  State stateTmp;
  Trigger *triggerTmp;
  std::vector<Trigger>::iterator itr;

  while(getPhrase() == true){
    if(this->phrase.type == TOKEN){
      strcpy(buf,this->phrase.buf);

      getPhrase();
      if(this->phrase.type == EXPRESSION){
        // <event>
        strcpy(buf, eventTmp.eventName);
        strcpy(this->phrase.buf, eventTmp.condition);

        event->push(eventTmp);
      }else if(this->phrase.type == L_PAR){
        // <state>

        // entry
        getPhrase();
        if(this->phrase.type == ENTRY){
          getPhrase();
          if(this->phrase.type == ENTRY_DO_EXIT_BLOCK){
            strcpy(buf, stateTmp.stateName);
            strcpy(this->phrase.buf, stateTmp.entryBlock);
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
            strcpy(buf, stateTmp.stateName);
            strcpy(this->phrase.buf, stateTmp.doBlock);
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
            strcpy(buf, stateTmp.stateName);
            strcpy(this->phrase.buf, stateTmp.exitBlock);
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
          triggerTmp = (Trigger*)malloc(sizeof(Trigger));

          if(this->phrase.type == TOKEN){
            getPhrase();
            if(this->phrase.type == ALLOW){
              getPhrase();
              if(this->phrase.type == TOKEN){
                strcpy(buf, triggerTmp->triggerName);
                strcpy(this->phrase.buf, triggerTmp->nextState);

                stateTmp.trigger_list.push_back(*triggerTmp);
              }else{
                fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
                return;
              }
            }else{
              fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
              return;
            }
          }else{
            break;
          }
        }

        // state-end
        getPhrase();
        if(this->phrase.type == R_PAR){

        }else{
          fprintf(stderr,"syntax error. Line %d\n",this->lineNo);
          return;
        }

        state->push(stateTmp);

        // triggerTmpŠJ•ú
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
