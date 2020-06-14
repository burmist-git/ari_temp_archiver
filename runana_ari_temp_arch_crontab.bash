#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Wed Nov 21 20:39:30 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  Program used to convert FEB temperature data in to  #
#                  2D TH2Poly histograms.                              #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

LC_TIME=en_US.UTF-8
source /home/hvala/root/bin/thisroot.sh
#source /home/burmist/root_v6.14.00/root-6.14.00-install/bin/thisroot.sh

function runana_ari_temp_arch_crontab_bash {
    $sourceHome/runana_ari_temp_arch $exeKeyID $rootFilesList $outRootFileF
    cp $outRootFileF /home/hvala/nishida6/data/root_pdf_summary/.
    cp $outRootFileF'.pdf' /home/hvala/nishida6/data/root_pdf_summary/.
}

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d  : default"
    echo " [0] -p2 : other"
    echo " [0] -h  : print help"
}

#sourceHome="/home/burmist/home2/ari_temp_archiver/"
sourceHome="/home/hvala/ari_temp_archiver/"

exeKeyID=0
rootFilesList=$sourceHome/rootFileList.dat;
outRootFileF=$sourceHome'aritemp-'$(date +%y%m%d)'_hist.root';

if [ $# -eq 0 ] 
then
    printHelp    
else
    if [ "$1" = "-d" ]; then
	runana_ari_temp_arch_crontab_bash
    elif [ "$1" = "-p2" ]; then
        printHelp
    elif [ "$1" = "-h" ]; then        
        printHelp        
    else
        printHelp
    fi
fi

#espeak "I have done"
