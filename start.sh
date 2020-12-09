#!/bin/tcsh -fv

if ($# != 1 ) then
    echo "usage: $0 hostname"
    exit 1;
endif

foreach x ( `cat kids.txt` )
    echo "./kid ${1} ${x}";
    # ./kid $1 $x & ;
    ./kid $1 $x > $x.log & ;
end