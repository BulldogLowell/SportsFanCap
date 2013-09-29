#! /usr/bin/env python
import serial
import urllib2
import json
import argparse
import logging
import os
import time
import signal
import sys
from pprint import pprint

def exit_handler(signal, frame):
    sys.exit(0)

def health(myteam, theirteam, final):
    if (final):
        if (myteam>theirteam):
            return 'w'
        if (myteam==theirteam):
            return 't'
        return 'l'        
    if (myteam==theirteam):
        return 'c'
    if (myteam-theirteam>9):
        return 'e'
    if (myteam-theirteam>0):
        return 'd'
    if (theirteam-myteam>9):
        return 'a'
    if (theirteam-myteam>0):
        return 'b'

signal.signal(signal.SIGINT, exit_handler)
signal.signal(signal.SIGTERM, exit_handler)

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Script to fetch sports scores and push to serial port'
    )

    parser.add_argument(
        '-d', '--device',
        help='device name',
        type=str,
        default="/dev/tty.usbserial-AD0265VB"
    )

    parser.add_argument(
        '-t', '--team',
        help='team name',
        type=str,
        default="OAK"
    )


    parser.add_argument(
        '-v', '--verbose',
        help='verbose output',
        action="store_true"
    )

    parser.add_argument(
        '--once',
        help='run once',
        action="store_true"
    )

    parser.add_argument(
        '--delay',
        help='refresh delay',
        type=int,
        default=5
    )

    args = parser.parse_args()

    logging.basicConfig(
        format='%(asctime)s %(levelname)s: %(message)s',
        level = logging.DEBUG if args.verbose else logging.ERROR
    )

    API_URL = "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20xml%20where%20url%3D%22http%3A%2F%2Fwww.nfl.com%2Fliveupdate%2Fscorestrip%2Fss.xml%22%20%20and%20itemPath%3D%22%2F%2Fg%5B%40h%3D'" + args.team + "'%20or%20%40v%3D'" + args.team + "'%5D%5B1%5D%22&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback="

    ser = serial.Serial(
        port = args.device,
        baudrate = 9600,
        parity = serial.PARITY_NONE,
        stopbits = serial.STOPBITS_ONE,
        bytesize = serial.EIGHTBITS
    )
    time.sleep(1)

    state = False
    while ( True ):
        scores = {}
        isfinal = False
        request = urllib2.Request( API_URL )
        response = urllib2.urlopen( request )
        data = json.loads( response.read() )

        results = data[ 'query' ]['results']
        scores[results['g']['h']] = int(results['g']['hs'])
        scores[results['g']['v']] = int(results['g']['vs'])
        if (results['g']['q'] == 'F'):
            isfinal = True
        else:
            isfinal = False
        pprint(scores)


        logging.debug( 'Sending to {device}: {char}'.format( device = args.device, char = state ) )
        ser.write( health (scores['OAK'], scores['WAS'], isfinal) )

        if ( args.once ):
            break
        
        time.sleep( args.delay )