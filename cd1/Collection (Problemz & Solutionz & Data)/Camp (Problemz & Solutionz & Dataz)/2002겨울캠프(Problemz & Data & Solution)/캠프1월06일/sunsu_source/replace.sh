#!/bin/sh

/bin/cat $1 | /bin/sed "1,$ s/%Ryu-Geun-Moon%/$2/g" 
