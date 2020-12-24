#ifndef _C_VOCABCARD_H_
#define _C_VOCABCARD_H_

#include <string>

#include "CMode.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"
#include "CUtil.h"
#include "CSound.h"
#include "CMask.h"

#include "CConfig.h"

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
  SLANG         = 0x2000,
};

struct CVocabcard {
  std::string romajikana;
  std::string english;
  short vocabtype;
  short JLPT_rank;
  short lesson_ID;
  short topic_ID;
};

#endif
