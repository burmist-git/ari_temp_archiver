#! /usr/bin/python3
# 2018.07.20: First version (psh)
# 2019.04.15: version for python3 (Rok Pestotnik)
# 2019.04.21: optimisation of the time window (Leonid Burmistrov)

import os
import sys
import argparse
import time
import urllib.request
import datetime

def getArchData(archURL, file_format, date_from, date_to, pv_name, data_home):
    url = archURL + '/retrieval/data/getData.' + file_format + '?'
    url = url + 'from=' + date_from + 'T00%3A00%3A00.000Z&'
    url = url + 'to=' + date_to + 'T23%3A59%3A59.000Z&'
    #from=2019-04-23T00%3A00%3A00.000Z&to=2019-04-23T23%3A59%3A59.000Z
    #from=2019-04-23T00%3A00%3A00.000Z&to=2019-04-23T11%3A23%3A59.000Z
    #url = url + 'from=' + date_from + '%3A00%3A00.000Z&'
    #url = url + 'to=' + date_to + '%3A23%3A59.000Z&'
    url = url + 'pv=' + pv_name + '&'
    url = url + 'nanos'
    print("Downloading", pv_name, "using url", url)
    input_file  = urllib.request.urlretrieve(url, data_home + pv_name.replace(':', '_') + '.' + file_format)
    return

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("archURL", help="This is the EPICS Archiver Appliance address with port. For example, http://172.22.16.73:17668")
    parser.add_argument("file_format", help="json, csv, mat, pb, txt, and svg")
    parser.add_argument("date_from", help="ISO 8601 format with date and hour. For example, 2018-07-20T14")
    parser.add_argument("date_to", help="ISO 8601 format with date and hour. For example, 2018-07-20T14")
    parser.add_argument("pv_list", help="pv list file")
    parser.add_argument("data_home", help="output data location")
    args = parser.parse_args()
    lines = []
    with open(args.pv_list, 'r') as f:
        lines = f.readlines()
    pv_name = []
    for line in lines:
        pv_name = line.strip()
        #print('line    = {}'.format(line))
        #print('pv_name = {}'.format(pv_name))
        getArchData( args.archURL, args.file_format, args.date_from, args.date_to, pv_name, args.data_home)
        time.sleep(1)
