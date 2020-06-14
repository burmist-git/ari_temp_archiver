#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Mon Apr 22 02:11:35 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

LC_TIME=en_US.UTF-8
#source /home/usr/hvala/root_v5.34.34/root/bin/thisroot.sh
source /home/hvala/root/bin/thisroot.sh
#source /home/burmist/root_v6.14.00/root-6.14.00-install/bin/thisroot.sh

function cleanData {
    echo "rm -f $1.root"
    rm -f $1.root
}

function converter {
    #echo "converter --> of the $1"

    exeKeyID=0
    nData=`(more $1 | grep secs | wc -l)`
    outRootF=$1'.root';
    $sourceHome/ari_temp_archiver_converter $exeKeyID $nData $outRootF $(more $1 | grep secs | sed 's/\,/ /' | sed 's/\,/ /' | awk {'print $3" "$5'} | xargs )

}

function ari_temp_archiver_converter_bash {
    fileArr=(
	$sourceHome/B2_nsm_get_MONKS_ARI_TEMP_1_value.json
	$sourceHome/B2_nsm_get_MONKS_ARI_TEMP_2_value.json
	$sourceHome/B2_nsm_get_MONKS_ARI_TEMP_3_value.json
	$sourceHome/B2_nsm_get_MONKS_ARI_TEMP_4_value.json
	$sourceHome/B2_nsm_get_MONKS_ARI_TEMP_5_value.json
	$sourceHome/B2_nsm_get_MONKS_ARI_TEMP_6_value.json
    )
    nn=${#fileArr[@]}
    let nn=nn-1
    
    for i in `seq 0 $nn`;
    do
	cleanData ${fileArr[$i]}
	converter ${fileArr[$i]}
    done
}

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d  : default"
    echo " [0] -h  : print help"
}

#sourceHome="/home/burmist/home2/ari_temp_archiver/"
sourceHome="/home/hvala/ari_temp_archiver/"

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	ari_temp_archiver_converter_bash
    elif [ "$1" = "-p2" ]; then
        printHelp
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
