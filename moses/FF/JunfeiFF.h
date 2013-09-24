#pragma once

#include <string>
#include "StatefulFeatureFunction.h"
#include "FFState.h"
#include "moses/ScoreComponentCollection.h"

namespace Moses
{

class JunfeiFFState : public FFState
{
public:
	int Compare(const FFState& other) const
	{
		return 0;
	}
};

class JunfeiFF : public StatefulFeatureFunction
{
public:
	JunfeiFF(const std::string &line)
		:StatefulFeatureFunction("JunfeiFF", 2, line)
		{}

	bool IsUseable(const FactorMask &mask) const
		{ return true; }

	void Evaluate(const Phrase &source
	                        , const TargetPhrase &targetPhrase
	                        , ScoreComponentCollection &scoreBreakdown
	                        , ScoreComponentCollection &estimatedFutureScore) const
	{}
	void Evaluate(const InputType &input
	                        , const InputPath &inputPath
	                        , const TargetPhrase &targetPhrase
	                        , ScoreComponentCollection &scoreBreakdown) const
	{}
	  FFState* Evaluate(
	    const Hypothesis& cur_hypo,
	    const FFState* prev_state,
	    ScoreComponentCollection* accumulator) const
	  {
		std::vector<float> scores(2);
		scores[0] = 2345345;
		scores[1] = 12312;
		accumulator->PlusEquals(this, scores);
		  return new JunfeiFFState();
	  }

	  FFState* EvaluateChart(
	    const ChartHypothesis& /* cur_hypo */,
	    int /* featureID - used to index the state in the previous hypotheses */,
	    ScoreComponentCollection* accumulator) const
	  {
		  return new JunfeiFFState();
	  }

	  virtual const FFState* EmptyHypothesisState(const InputType &input) const
	  {
		  return new JunfeiFFState();
	  }


};


}

