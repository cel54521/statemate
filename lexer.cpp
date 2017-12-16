#include <string.h>
#include "lexer.h"

Lexer::Lexer(FILE *in, FILE *out){
  this->in = in;
  this->out = out;

  bufno = 0;
}


void Lexer::analyze(void){
  int bufno = 0;
  char buf[1024];

  getNextChar();

  while(EOF != c){
    if(this->isLexicalGroup(c, ALPHABET)){
      analyzeToken();
      fprintf(this->out, "TOKEN,%s\n", this->buf);

    }else if(this->isLexicalGroup(c, WHITESPACE)){
      do{
        getNextChar();
      }while(this->isLexicalGroup(c, WHITESPACE));
    }else if(c == '{'){
      fprintf(this->out, "LPAR,{\n");
      getNextChar();
    }else if(c == '}'){
      fprintf(this->out, "RPAR,}\n");
      getNextChar();
    }else if(c == '-'){
      this->clearToken();
      this->addToken(c);
      getNextChar();
      if(c == '>'){
        fprintf(this->out, "ALLOW,->\n");
        getNextChar();
      }
    }else{
      getNextChar();
    }
  }
}

void Lexer::getNextChar(void){
  this->c = fgetc(in);
}

void Lexer::analyzeToken(void){
  this->clearToken();

  while( (this->c != EOF) && this->isLexicalGroup(this->c, ALPHABET)){
    this->addToken(this->c);
    getNextChar();

    while(this->isLexicalGroup(this->c, WHITESPACE)){
      fprintf(stderr,"%c",c);
      getNextChar();
    }
  }
}

bool Lexer::isLexicalGroup(char c, const char *group){
  int i;
  int len;

  len = strlen(group);

  for(i = 0; i < len; i++){
    if(group[i] == c){
      return true;
    }
  }

  return false;
}

bool Lexer::isKeywords(char *buf){

}

void Lexer::addToken(char c){
  if(this->bufno < 1022){
    this->buf[this->bufno] = c;
    this->buf[this->bufno+1] = '\0';
    this->bufno++;
  }
}

void Lexer::clearToken(void){
  this->bufno = 0;
  this->buf[this->bufno] = '\0';
}
