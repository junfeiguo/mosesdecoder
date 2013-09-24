// $Id$

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#include "util/check.hh"
#include <limits>
#include <iostream>
#include <fstream>

#include "Junfei.h"
#include "moses/TypeDef.h"
#include "moses/Util.h"
#include "moses/FactorCollection.h"
#include "moses/Phrase.h"
#include "moses/StaticData.h"

// By default, SRILM defines a function called zopen.
// 
// However, on Mac OS X (and possibly other BSDs),
// <stdio.h> already defines a zopen function.
//
// To resolve this conflict, SRILM checks to see if HAVE_ZOPEN is defined.
// If it is, SRILM will rename its zopen function as my_zopen.
//
// So, before importing any SRILM headers, 
// it is important to define HAVE_ZOPEN if we are on an Apple OS:
//
#ifdef __APPLE__
#define HAVE_ZOPEN
#endif


using namespace std;

namespace Moses
{
LanguageModelJunfei::LanguageModelJunfei(const std::string &line)
  :LanguageModelSingleFactor("JunfeiLM", line)
{
  ReadParameters();
}

LanguageModelJunfei::~LanguageModelJunfei()
{

}

void LanguageModelJunfei::Load()
{
  FactorCollection &factorCollection = FactorCollection::Instance();

  m_sentenceStart = factorCollection.AddFactor(Output, m_factorType, BOS_);
  m_sentenceStartWord[m_factorType] = m_sentenceStart;

  m_sentenceEnd		= factorCollection.AddFactor(Output, m_factorType, EOS_);
  m_sentenceEndWord[m_factorType] = m_sentenceEnd;

}

LMResult LanguageModelJunfei::GetValue(const vector<const Word*> &contextFactor, State* finalState) const
{
  LMResult ret;
  FactorType	factorType = GetFactorType();
  size_t count = contextFactor.size();
  if (count <= 0) {
    if(finalState)
      *finalState = NULL;
    ret.score = 0.0;
    ret.unknown = false;
    return ret;
  }


  cerr << "Junfei's word sequence :";
  for (int i = 0; i < contextFactor.size(); ++i) {
    const Word &word = *contextFactor[i];
    cerr << word << " ";
  }
  cerr << endl;

  ret.score = 1;


  return ret;
}

}





