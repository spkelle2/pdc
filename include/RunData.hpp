/**
 * @file RunData.hpp
 * @author Sean Kelley
 * @date 2023-03-03
 */

#ifndef RUNDATA_H_
#define RUNDATA_H_


// standard modules
#include <filesystem.hpp> // path
#include <string> // string

// namespaces
namespace fs = ghc::filesystem;

/** A data class to track specifics on a given solved MIP instance */
struct RunData {
public:

  // primary keys

  /** the index of the instance */
  int instanceIndex;

  /** The method used for generating VPCs */
  std::string vpcGenerator;

  /** The number of active leaves in the partial branch and bound tree from which
   * we get a disjunction that generated VPCs */
  int terms;

  // bound stats

  /** the dual bound after solving the root LP relaxation for each instance */
  double lpBound;

  /** the dual bound of the disjunctions that generated this instances vpcs */
  double disjunctiveDualBound;

  /** the dual bound after solving the root LP relaxation and applying VPCs for each instance */
  double lpBoundPostVpc;

  /** the dual bound after running cut generation on the root node */
  double rootDualBound;

  /** the best found dual bound for each instance */
  double dualBound;

  /** the best found primal bound for each instance */
  double primalBound;

  // time stats

  /** cumulative time through generating VPCs */
  double vpcGenerationTime;

  /** cumulative time to complete cut generation on root node */
  double rootDualBoundTime;

  /** cumulative time to find best integer feasible solution */
  double bestSolutionTime;

  /** cumulative time to end of branch and cut call */
  double terminationTime;

  // misc performance stats

  /** number of branch and bound nodes */
  int nodes;

  /** number of LP simplex iterations */
  int iterations;

  // misc statistics

  /** max run time given to solve */
  double maxTime;

  /** size of disjunction that generated vpcs */
  int actualTerms;

  /** number of vpcs generated */
  int numCuts;

  /** which mip solver was used */
  std::string mipSolver;

  /** was the primal bound provided or not */
  bool providePrimalBound;

  /** constructor (default) */
  RunData();

  /** copy constructor */
  RunData(const RunData& rhs);

  /** assignment operator */
  RunData& operator=(const RunData& rhs);

  /** clone */
  RunData* clone() const;

  /** Copy our stuff */
  void initialize(const RunData* const rhs);

  /** Get a comma-separated string of the names of RunData's attributes */
  std::string getHeader();

  /** Get a comma-separated string of the values of RunData's attributes */
  std::string getValues();

  /** writes this struct's attributes to the given csv file */
  void writeData(fs::path filePath);
};

#endif
