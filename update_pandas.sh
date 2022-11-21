#!/bin/bash

# Run this script in the directory containing yout .vfcrun.h5 files
# before running your vfc_ci serve command with :
# . update_pandas.sh

mkdir lib
pip install pandas==1.2.3 -t lib
export PYTHONPATH=$(pwd)/lib:$PYTHONPATH