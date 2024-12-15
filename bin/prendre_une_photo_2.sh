#!/bin/bash
#
#set -x


CAMERA=1
TIMEOUT=2000



for R in train valid test
do
	if [ $R = "train" ]; then NB=75; fi
	if [ $R = "valid" ]; then NB=15; fi
	if [ $R = "test" ]; then NB=15; fi

	for I in $(seq 1 $NB)
	do

		REP="../Dataset/Fred_Dataset/images_HD_2/"$R

		TIMESTAMP=`date +"%s"`
		FILE=${REP}"/"${TIMESTAMP}".jpg"

		echo $R $I - $FILE

		read -p "Press enter"

		rpicam-jpeg  --camera ${CAMERA} --output ${FILE} --timeout ${TIMEOUT} --autofocus-mode manual --lens-position 0.0
	done
done

