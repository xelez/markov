#!/bin/bash
cat ../tests/02_WarAndPeace.txt | ./markov.pl 1000000 2 > out.txt
echo 'OK'
