#!/bin/bash

python ../dpf/utils/png2rgba.py CS2_Art $(dirname $0)

#pushd $(dirname $0)/buttons/
#python ../../dpf/utils/png2rgba.py CS2_Art_Buttons .
#mv *.cpp *.hpp ../
#popd
