#!/bin/bash
#
set -x

REP="../Dataset/Fred_Dataset/images_HD/"

CAMERA=1
TIMEOUT=2000


TIMESTAMP=`date +"%s"`
FILE=${REP}"/"${TIMESTAMP}".jpg"


echo $FILE

rpicam-jpeg  --camera ${CAMERA} --output ${FILE} --timeout ${TIMEOUT} --autofocus-mode manual --lens-position 0.0
