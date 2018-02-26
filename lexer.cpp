/**
 * @file lexer.cpp
 * @brief statemateš‹å‰ğÍŠí
 * @author cel54521
 */
#include "lexer.h"
#include <string.h>
#include "keyword.h"

static const char *RESERVED_WORD[RESERVED_WORD_NUM] = {"entry","do","exit"};
static const char ALPHABET[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                             'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                             '_','\0'
};

static const char WHITESPACE[] = {
  ' ','\t','\n','\r','\0'
};

Lexer::Lexer(FILE *in, FILE *out)
{
  this->in = in;
  this->out = out;

  bufno = 0;
}


void Lexer::analyze(void)
{
  int bufno = 0;
  char buf[1024];

  getNextChar();

  while(EOF != c){
    if(this->isLexicalGroup(c, ALPHABET)){
      this->analyzeToken();

      switch(this->isKeywords(this->buf)){
      case ENTRY:
        fprintf(this->out, "ENTRY,%s\n", this->buf);

        break;
      case DO:
        fprintf(this->out, "DO,%s\n", this->buf);

        break;
      case EXIT:
        fprintf(this->out, "EXIT,%s\n", this->buf);

        break;
      default:
        fprintf(this->out, "TOKEN,%s\n", this->buf);

        break;
      }
    }else if(c == '['){
      this->analyzeEntryDoExitBlock();
      fprintf(this->out, "ENTRY_DO_EXIT_BLOCK,%s\n", this->buf);
      this->getNextChar();
    }else if(c == '('){
      this->analyzeExpression();
      fprintf(this->out, "EXPRESSION,%s\n", this->buf);
      this->getNextChar();
    }else if(this->isLexicalGroup(c, WHITESPACE)){
      do{
        this->getNextChar();
      }while(this->isLexicalGroup(c, WHITESPACE));
    }else if(c == '{'){
      fprintf(this->out, "L_PAR,{\n");
      this->getNextChar();
    }else if(c == '}'){
      fprintf(this->out, "R_PAR,}\n");
      this->getNextChar();
    }else if(c == '-'){
      this->clearToken();
      this->addToken(c);
      this->getNextChar();
      if(c == '>'){
        fprintf(this->out, "ALLOW,->\n");
        this->getNextChar();
      }
    }else{
      this->getNextChar();
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
    this->getNextChar();

    //while(this->isLexicalGroup(this->c, WHITESPACE)){
    //  this->getNextChar();
    //}
  }
}

void Lexer::analyzeEntryDoExitBlock(void){
  int parCount = 1;

  this->clearToken();

  //]‚Ü‚ÅEntryDoExitBlock‚Æ‚µ‚Ä“o˜^
  do{
    this->addToken(this->c);
    this->getNextChar();

    if(this->c == '['){
      parCount++;
    }else if(this->c == ']'){
      parCount--;
    }
  }while((this->c != EOF) && ((parCount != 0) || (this->c != ']')));

  if(this->c == ']'){
    this->addToken(this->c);
  }
}


void Lexer::analyzeExpression(void){
  int parCount = 1;

  this->clearToken();

  //)‚Ü‚ÅEntryDoExitBlock‚Æ‚µ‚Ä“o˜^
  do{
    this->addToken(this->c);
    this->getNextChar();

    if(this->c == '('){
      parCount++;
    }else if(this->c == ')'){
      parCount--;
    }
  }while((this->c != EOF) && ((parCount != 0) || (this->c != ')')));

  if(this->c == ')'){
    this->addToken(this->c);
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

int Lexer::isKeywords(char *buf){
  int i;

  for(i = 0;i < RESERVED_WORD_NUM; i++){
    if(strcmp(buf, RESERVED_WORD[i]) == 0){
      return i;
    }
  }

  return -1;
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
