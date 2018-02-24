/**
 * @file lexer.h
 * @brief statemateš‹å‰ğÍŠí
 * @author cel54521
 */
#ifndef _LEXER_
#define _LEXER_

#include <stdio.h>

class Lexer{
 private:
  FILE *in;
  FILE *out;
  char c;
  char buf[10240];
  int bufno;

  bool isLexicalGroup(char c, const char *group);
  int isKeywords(char *buf);
  void addToken(char c);
  void clearToken(void);
  void getNextChar(void);
  void analyzeToken(void);
  void analyzeEntryDoExitBlock(void);
  void analyzeExpression(void);
 public:
  Lexer(FILE *in, FILE *out);
  void analyze(void);

};

#endif
