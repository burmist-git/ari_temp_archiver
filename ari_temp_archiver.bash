#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Sun Apr 21 12:46:16 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function get_ARI_TEMP {
    #data_start=`(date +%Y-%m-%dT00)`
    #data_stop=`(date +%Y-%m-%dT%H)`
    data_start=`(date +%Y-%m-%d)`
    data_stop=`(date +%Y-%m-%d)`
    echo "data_start = $data_start:00:00:00"
    echo "data_stop  = $data_stop:23:59:59"
    python3 $sourceHome/getArchivedData.py $hostName:$portID json $data_start $data_stop $pvlist_txt $sourceHome
}

function get_ARI_TEMP_date {
    data_start=$1
    data_stop=$2
    echo "data_start = $data_start:00:00:00"
    echo "data_stop  = $data_stop:23:59:59"
    python3 $sourceHome/getArchivedData.py $hostName:$portID json $data_start $data_stop $pvlist_txt $sourceHome
}

function printHelp {
    echo " --> ERROR in input arguments "
    echo " $sourceHome/getArchivedData.py -h "
    python3 $sourceHome/getArchivedData.py -h
    echo " "
    echo " "
    echo " [0] -d-ARICH_t : get data of ARICH ambient temperature for a current day (JST)"
    echo " [1]            : START date : to be analyzed (Format example : 2019-04-23)"
    echo " [2]            : STOP  date : to be analyzed (Format example : 2019-04-23)"
    echo " [0] -h         : print help"
}

portID='17668'
#hostName="http://localhost"
#hostName="http://172.22.16.120"
hostName='http://'$(host b2arch1.daqnet.kek.jp | awk '{print $4}')
#sourceHome="/home/burmist/home2/ari_temp_archiver/"
sourceHome="/home/hvala/ari_temp_archiver/"
pvlist_txt=$sourceHome'ARI_TEMP.pvlist.txt'

if [ $# -eq 0 ]
then    
    printHelp
else
    if [ "$1" = "-d-ARICH_t" ]; then    
        if [ $# -eq 3 ]
        then   
            inDateStart=$2
	    inDateStop=$3
	    get_ARI_TEMP_date $inDateStart $inDateStop
        elif [ $# -eq 1 ]; then
	    get_ARI_TEMP
        else
            printHelp
        fi
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi   
fi
