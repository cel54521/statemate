/**
 * @file parser.h
 * @brief statemate\•¶‰ğÍŠí
 * @author cel54521
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <string.h>
#include <vector>
#include "Event.h"
#include "State.h"

typedef struct _Phrase{
  int type;
  char buf[10240];
}Phrase;


class Parser{
 private:
  FILE *in;
  FILE *out;

  Phrase phrase;
  int lineNo;

  bool getPhrase(void);

 public:
  Parser(FILE *in, FILE *out);
  void analyze(EventList* const event, StateList* const state);
};

#endif
