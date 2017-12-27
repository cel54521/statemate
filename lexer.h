/**
 * @file lexer.h
 * @brief statemateéöãÂâêÕäÌ
 * @author cel54521
 */
#ifndef _LEXER_
#define _LEXER_

#include <stdio.h>

#define TOKEN 0
#define R_PAR 1
#define L_PAR 2

#define KEYWORD_NUM 3

enum keywords {
  Entry,
  Do,
  Exit
};


const char *keywords[KEYWORD_NUM] = {"entry","do","exit"};
const char ALPHABET[]={
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
  '_','\0'
};


const char WHITESPACE[]={' ','\t','\n','\r','\0'};
class Lexer{
 private:
  FILE *in;
  FILE *out;
  char c;
  char buf[1024];
  int bufno;

  bool isLexicalGroup(char c, const char *group);
  int isKeywords(char *buf);
  void addToken(char c);
  void clearToken(void);
  void getNextChar(void);
  void analyzeToken(void);
 public:
  Lexer(FILE *in, FILE *out);
  void analyze(void);

};

#endif
