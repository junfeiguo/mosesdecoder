#pragma once

#include "FeatureFunction.h"
#include "util/check.hh"
#include "moses-cmd/SearchGraph.h"

namespace Moses
{

/** base class for all stateless feature functions.
 * eg. phrase table, word penalty, phrase penalty
 */
class StatelessFeatureFunction: public FeatureFunction
{
  //All stateless FFs, except those that cache scores in T-Option
  static std::vector<const StatelessFeatureFunction*> m_statelessFFs;

public:
  static std::vector<std::vector<const StatelessFeatureFunction*> > m_passes;

  static const std::vector<const StatelessFeatureFunction*>& GetStatelessFeatureFunctions(size_t pass) {
	CHECK(pass < m_passes.size());
	return m_passes[pass];
  }
  static const std::vector<const StatelessFeatureFunction*>& GetAllStatelessFF() {
    return m_statelessFFs;
  }

  StatelessFeatureFunction(const std::string& description, const std::string &line);
  StatelessFeatureFunction(const std::string& description, size_t numScoreComponents, const std::string &line);

  using FeatureFunction::Evaluate;
  /**
    * This should be implemented for features that apply to phrase-based models.
    **/
  virtual void Evaluate(const Hypothesis& hypo,
                        ScoreComponentCollection* accumulator) const = 0;

  /**
    * Same for chart-based features.
    **/
  virtual void EvaluateChart(const ChartHypothesis &hypo,
                             ScoreComponentCollection* accumulator) const = 0;

  virtual void Evaluate(SearchGraph::Edge &edge ) const
  {}

  virtual bool IsStateless() const {
    return true;
  }

};


} // namespace

