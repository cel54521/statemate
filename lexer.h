/**
 * @file lexer.h
 * @brief statemateéöãÂâêÕäÌ
 * @author cel54521
 */
#ifndef _LEXER_
#define _LEXER_

#define RESERVED_WORD_NUM 3

typedef enum _keyword {
  ENTRY,
  DO,
  EXIT,
  TOKEN = RESERVED_WORD_NUM + 1,
  R_PAR,
  L_PAR,
  R_BRACKET,
  L_BRACKET,
  ENTRY_DO_EXIT_BLOCK,
  EXPRESSION
} keyword;

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
