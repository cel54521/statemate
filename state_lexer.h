/**
 * @file lexer.h
 * @brief statemateéöãÂâêÕäÌ
 * @author cel54521
 */
#ifndef _LEXER_
#define _LEXER_

#include <stdio.h>

class StateLexer {
private:
    FILE *in;
    FILE *out;
    char c;
    char buf[10240];
    int bufno;

    void analyzeEntryDoExitBlock(void);
    void analyzeExpression(void);
protected:
    static const char *RESERVED_WORD[];
    static const char ALPHABET[];
    static const char WHITESPACE[];

    bool isLexicalGroup(char c, const char *group);
    int isKeywords(char *buf);
    void addToken(char c);
    void clearToken(void);
    void getNextChar(void);
    void analyzeToken(void);
public:
    enum _keyword {
      ENTRY,
      DO,
      EXIT,
      TOKEN = 10,
      R_PAR,
      L_PAR,
      ALLOW,
      R_BRACKET,
      L_BRACKET,
      ENTRY_DO_EXIT_BLOCK,
      EXPRESSION,
      UNKNOWN
    };
    StateLexer(FILE *in, FILE *out);
    void analyze(void);

};

#endif
