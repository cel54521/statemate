#include <stdio.h>
#include <vector>

#define __DEBUG__


#include "lexer.h"
#include "parser.h"
#include "event.h"
#include "state.h"


int main(void){
  FILE *in;
  FILE *tmp1;
  FILE *tmp2;
  FILE *out;
  Lexer *lexer;
  Parser *parser;
  EventList *event;
  StateList *state;

  event = new EventList();
  state = new StateList();

#ifdef __DEBUG__
  std::vector<Event>::iterator eventItr;
  std::vector<State>::iterator stateItr;
#endif

  if((in = fopen("states.sta","r")) == NULL){
    fprintf(stderr,"sta file not found\n");
  }

  if((tmp1 = fopen("states.tmp","w")) == NULL){
    fprintf(stderr,"tmp create or read error\n");
  }

  // éöãÂâêÕ
  lexer = new Lexer(in, tmp1);
  lexer->analyze();

  fclose(in);
  fclose(tmp1);

  if((tmp2 = fopen("states.tmp","r")) == NULL){
    fprintf(stderr,"tmp create or read error\n");
  }

  if((out = fopen("states.out","w")) == NULL){
    fprintf(stderr,"out create error\n");
  }

  // ç\ï∂âêÕ
  parser = new Parser(tmp2, out);
  parser->analyze(event, state);

  fclose(out);
  fclose(tmp2);

#ifdef __DEBUG__
  fprintf(stderr,"DEBUG OUTPUT\n");

  event->print();
  state->print();
#endif

  if(lexer != NULL){
    delete lexer;
  }

  // ç\ï∂âêÕ


  return 0;
}
