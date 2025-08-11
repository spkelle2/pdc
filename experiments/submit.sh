#!/bin/bash

cd /home/sek519/warm_starting/pdc/experiments
source /home/sek519/.bashrc
source /home/sek519/miniconda/bin/activate

# Your command
../Release/pdc ${INPUT_FOLDER} ${OUTPUT_FILE} ${MAX_TIME} ${GENERATOR} ${TERMS} ${MIP_SOLVER} ${PROVIDE_PRIMAL_BOUND}