/**
 * @file parser.h
 * @brief statemateç\ï∂âêÕäÌ
 * @author cel54521
 */
#ifndef _PARSER_H_
#define _PARSER_H_

enum _type {
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
};


class Parser{
 private:
  FILE *in;
  FILE *out;

  int type;

  void getPhrase(void);
 public:
  Parser(FILE *in, FILE *out);
}

#endif
(+ 1 2)
