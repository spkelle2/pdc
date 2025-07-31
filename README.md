# Parametric Disjunctive Cuts

A library parameterizing disjunctive inequalities to provide a warm start to the cut pool for a series of mixed-integer linear programs.

### Instructions for `Eigen`
Clone the `Eigen` library to your machine and properly link to it in the `Makefile` with the `EIG_LIB` variable.
    git clone https://gitlab.com/libeigen/eigen.git

### Instructions for `VPC` submodule
Note: The submodule for the `VPC` generator is not necessary if you have the `VPC` repository elsewhere on your machine and you properly set the `VPC_DIR` variable in the `Makefile`.

Whenever the repository is cloned on a new machine, there are several steps to get the required dependencies (from `COIN-OR` and the `VPC` cut generator). The `VPC` generator is added as a submodule, which is kept on record in the `.gitmodules` file. After cloning the main repository, the user must run `git submodule init`, then `git submodule update`. Alternatively, when calling `git clone` initially, one can call `git clone --recurse-submodules`.

Afterwards, `cd` to the `vpc` directory, call `export PROJ_DIR=$PWD` from that directory, and call `./setup/install_coin.sh` to install `COIN-OR` files into `vpc/lib`.

Then, still in the `vpc` directory, modify the `makefile` to properly set the COIN and CPLEX directories and set `USE_CPLEX` to value `1`. Finally, call `make` then `make archive`.

### Instructions for Running Unit Tests
Instead of building with `make debug` or `make release`, call `make unit_test
UNIT_TEST_FILE=<test_subdir>/<test_file>.cpp` to build the corresponding unit tests.
For example, `make unit_test UNIT_TEST_FILE=test_cut/TestVwsSolverInterface.cpp`
will build the unit tests in `src/test/test_cut/TestVwsSolverInterface.cpp` as the
executable `UnitTest/UnitTest`. See the [Catch2 documentation](https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md)
for the executable's command line interface.
