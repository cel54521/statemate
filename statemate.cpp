#include <stdio.h>
#include <vector>
#include "lexer.h"
#include "parser.h"
#include "event.h"
#include "state.h"

#define __DEBUG__

int main(void){
  FILE *in;
  FILE *tmp;
  FILE *out;
  Lexer *lexer;
  Parser *parser;
  Event event;
  State state;

#ifdef __DEBUG__
  std::vector<Event>::iterator eventItr;
  std::vector<State>::iterator stateItr;
#endif

  if((in = fopen("states.sta","r")) == NULL){
    fprintf(stderr,"sta file not found\n");
  }

  if((tmp = fopen("states.tmp","w+")) == NULL){
    fprintf(stderr,"tmp create or read error\n");
  }

  if((out = fopen("states.out","w")) == NULL){
    fprintf(stderr,"out create error\n");
  }

  // éöãÂâêÕ
  lexer = new Lexer(in, tmp);
  lexer->analyze();

  // ç\ï∂âêÕ
  parser = new Parser(tmp, out);
  parser->analyze(&event, &state);

#ifdef __DEBUG__
  fprintf(stderr,"DEBUG OUTPUT\n");

  for(eventItr = event.begin(); eventItr < event.end(); eventItr++){

  }

  for(stateItr = state.begin(); stateItr < state.end(); stateItr++){
    fprintf(stderr, "%s,entry=%s,do=%s,exit=%s\n", stateItr->stateName, stateItr->entryBlock, stateItr->doBlock, stateItr->exitBlock);
  }
#endif

  if(lexer != NULL){
    delete lexer;
  }

  // ç\ï∂âêÕ


  return 0;
}
