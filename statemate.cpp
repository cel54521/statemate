#include <stdio.h>
#include "lexer.h"

int main(void){
  FILE *in;
  FILE *tmp;
  Lexer *lexer;

  if((in = fopen("states.sta","r")) == NULL){
    fprintf(stderr,"sta file not found\n");
  }

  if((tmp = fopen("states.tmp","w")) == NULL){
    fprintf(stderr,"tmp create error\n");
  }

  lexer = new Lexer(in, tmp);

  lexer->analyze();

  if(lexer != NULL){
    delete lexer;
  }

  return 0;
}
