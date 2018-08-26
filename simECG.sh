 #!/bin/sh
    appname=`basename $0 | sed s,\.sh$,,`
    dirname=`dirname $0`
    LD_LIBRARY_PATH=$PWD/$dirname/libs:/usr/lib
    export LD_LIBRARY_PATH
    $PWD/$dirname/$appname $*
