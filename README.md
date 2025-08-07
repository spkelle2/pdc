# Parametric Disjunctive Cuts (pdc)

A library parameterizing disjunctive inequalities to provide a warm start to the
cut pool for a series of mixed-integer linear programs (MILPs). More details can be found
in the papers [Warm Starting Series of Mixed-Integer Linear Optimization Problems
with Parametric Disjunctive Cuts](papers/parametric_disjunctive_cuts.pdf) and
[Strengthing Parametric Disjunctive Cuts](papers/strengthening.pdf).

### Installation Instructions

1. Clone this repository.

2. This project depends on [my fork](https://github.com/spkelle2/vpc) of VPC. Clone
it and follow the instructions in its README to build and install VPC. The makefile
for PDC assumes that PDC and VPC are cloned to the same directory.

3. This project also depends on Gurobi. Go 
[here](https://support.gurobi.com/hc/en-us/articles/14799677517585-Getting-Started-with-Gurobi-Optimizer)
for its installation instructions. Afterwards, you will need to update the paths
in the Makefile under variables user should set to reflect your installation.:
   * GUROBI_DIR (the root directory where Gurobi is installed)
   * GUROBI_LINK (base name of the Gurobi shared library)
   
4. There are two main compilation modes: debug and release. These can be compiled
with `make debug` or `make release`, which creates the executable `pdc` in a new
subdirectory Debug or Release of the main folder of this repository.

5. The executable `pdc` can be run via the command line with the following required
positional arguments:
    * input folder: path to a folder containing of `.mps` files of MILP instances
fixed in dimension.
    * output file: path to a non-existent .csv file to which results will be written.
    * max run time: maximum time in seconds to allow each instance to generate disjunctive
cuts and solve the MILP.
    * cut generator: which disjunctive cut generator to use. Options are:
        * None: No disjunctive cuts are generated.
        * New: Generates disjunctive cuts for all instances via VPC with a new
        disjunction for each instance.
        * Old: Generates disjunctive cuts for all instances via VPC with the same
        disjunction throughout.
        * Farkas: Generates disjunctive cuts for the first instance via VPC and
        then uses those cuts' Farkas multipliers to generate parametric disjunctive
        cuts for all subsequent instances.
    * disjunctive terms: the number of disjunctive terms to use in the disjunction
for generating disjunctive cuts. Must be at least 2.
    * solver: which MILP solver to use. Options are:
        * Gurobi: Uses Gurobi to solve the MILPs.
        * CBC: Uses Coin-OR Branch-and-Cut to solve the MILPs.
    * primal bound: a known primal bound on the MILP instances. Can use a high value
   like 1e+20 if no good primal bound is known.
    * seed index: An index to refer to this run. This is useful when running
   multiple times to differentiate the runs.
    * tighten disjunction: whether or not to use previously found solutions to 
   prune the disjunction prior to generating disjunctive cuts. Options are:
        * 0: Do not tighten the disjunction.
        * 1: Tighten the disjunction.
    * tighten matrix perturbation: whether or not to tighten parametric disjunctive
    cuts when changes to the constraint matrix are detected. Options are:
        * 0: Do not tighten parametric disjunctive cuts.
        * 1: Tighten parametric disjunctive cuts.
    * tighten infeasible to feasible term: whether or not to tighten parametric
    disjunctive cuts for terms that are infeasible for the first instance but
    feasible in subsequent instances. Options are:
        * 0: Do not tighten parametric disjunctive cuts.
        * 1: Tighten parametric disjunctive cuts.
    * tighten feasible to infeasible basis: whether or not to tighten parametric
      disjunctive cuts when the supporting basis becomes infeasible in subsequent
      instances. Options are:
        * 0: Do not tighten parametric disjunctive cuts.
        * 1: Tighten parametric disjunctive cuts.

    An example command from this directory to run the executable against
    perturbations of `bm23.mps` with strengthened parametric disjunctive cuts is:
    ```
    ../<compilation_mode>/pdc src/test/test_instances/bm23 output_file.csv 60 Farkas 64 Gurobi 34 0 1 1 1 1
    ```

### Instructions for Running Unit Tests
Instead of building with `make debug` or `make release`, call `make unit_test
UNIT_TEST_FILE=<test_subdir>/<test_file>.cpp` to build the corresponding unit tests.
For example, `make unit_test UNIT_TEST_FILE=test_cut/TestPdcSolverInterface.cpp`
will build the unit tests in `src/test/test_cut/TestPdcSolverInterface.cpp` as the
executable `UnitTest/UnitTest`. See the [Catch2 documentation](https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md)
for the executable's command line interface.
