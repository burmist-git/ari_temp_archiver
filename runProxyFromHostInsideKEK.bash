#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Sun Apr 21 10:43:00 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function runProxyFromHostInsideKEK_bash {
    #sshpass -f mpfile.ariterm1 ssh -L $portID:b2arch1.daqnet.kek.jp:$portID -f -N burmist@bdaq.local.kek.jp
    ssh -L $portID:b2arch1.daqnet.kek.jp:$portID -f -N burmist@bdaq.local.kek.jp
}

function showTheTunnelOnPort {
    sudo lsof -i -n | grep $portID
    sudo lsof -i -n | grep $portID | wc -l
    tunnelProcessID=`(sudo lsof -i -n | grep $portID | grep $portID | grep :: | awk {'print $2'})`
    echo "tunnelProcessID = $tunnelProcessID"
    if [ "$1" = "-k" ]; then    
	kill -9 $tunnelProcessID
    fi
}

function pingb2arch1 {
    ping -c 3 b2arch1.daqnet.kek.jp
}

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d  : default "
    echo " [0] -ts : show the tunnel on the port : $portID"
    echo " [0] -k  : close the tunnel on the port : $portID"
    echo " [0] -p  : pingin b2arch1"
}

portID='17668'

if [ $# -eq 0 ]
then    
    printHelp
else
    if [ "$1" = "-d" ]; then    
	runProxyFromHostInsideKEK_bash
    elif [ "$1" = "-ts" ]; then
        showTheTunnelOnPort
    elif [ "$1" = "-k" ]; then
        showTheTunnelOnPort -k
    elif [ "$1" = "-p" ]; then
	pingb2arch1
    else
        printHelp
    fi   
fi
