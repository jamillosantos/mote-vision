#!/bin/bash
scriptpath="`dirname \"$0\"`"
scriptpath="`( cd \"$scriptpath\" && pwd )`"
cd $scriptpath/bin/debug
rm -R *
cmake -config Debug ../..
