#include <stdio.h>
#include "lexer.h"

int main(void){
  FILE *in;
  FILE *tmp;
  FILE *out;
  Lexer *lexer;

  if((in = fopen("states.sta","r")) == NULL){
    fprintf(stderr,"sta file not found\n");
  }

  if((tmp = fopen("states.tmp","rw")) == NULL){
    fprintf(stderr,"tmp create or read error\n");
  }

  if((out = fopen("states.out","w")) == NULL){
    fprintf(stderr,"out create error\n");
  }

  // š‹å‰ğÍ
  lexer = new Lexer(in, tmp);
  lexer->analyze();

  if(lexer != NULL){
    delete lexer;
  }

  // \•¶‰ğÍ


  return 0;
}
