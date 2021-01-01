#ifndef _C_VOCABCARD_H_
#define _C_VOCABCARD_H_

#include <string>

enum { // vocabtypes
  UNKNOWN       = 0,
  NOUN          = 0x0001,
  PRONOUN       = 0x0002,
  ADJECTIVE     = 0x0004,
  I_ADJECTIVE   = 0x0008,
  NA_ADJECTIVE  = 0x0010,
  VERB          = 0x0020,
  U_VERB        = 0x0040,
  RU_VERB       = 0x0080,
  ADVERB        = 0x0100,
  CONJUNCTION   = 0x0200,
  PREPOSITION   = 0x0400,
  IRREGULAR     = 0x0800,
  PHRASE        = 0x1000,
  FORMAL        = 0x2000,
  CASUAL        = 0x4000,
  SLANG         = 0x8000,
};

struct CVocabcard {
  std::string jp;
  std::string kana;
  std::string en;
  short vocabtype;
  short JLPT_rank;
  short lesson_ID;
  short topic_ID;
  CVocabcard(): vocabtype(UNKNOWN), JLPT_rank(0), lesson_ID(0), topic_ID(0) {};
};

#endif
