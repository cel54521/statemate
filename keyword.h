#ifndef _KEYWORD_H_
#define _KEYWORD_H_

#define RESERVED_WORD_NUM 3

enum _keyword {
  ENTRY,
  DO,
  EXIT,
  TOKEN = RESERVED_WORD_NUM + 1,
  R_PAR,
  L_PAR,
  ALLOW,
  R_BRACKET,
  L_BRACKET,
  ENTRY_DO_EXIT_BLOCK,
  EXPRESSION,
  UNKNOWN
};

#endif
