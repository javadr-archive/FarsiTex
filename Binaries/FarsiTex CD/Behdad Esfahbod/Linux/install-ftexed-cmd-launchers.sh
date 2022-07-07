#!/bin/bash

# Create launcher shell script that converts windows file names to unix
cat > ~/bin/ftexed-launch-cmd.sh <<\END
if test "x$1" = "x--run-n-stop"; then shift; "$@" || read; exit; fi
run=$1; filename=$2; shift 2; ext=; noterm=false;
if test "x$run" != "x${run%.exe}"; then run="`basename ${run%.exe}`"; fi
case $run in dvips) ext=.dvi; set -- "$@" -o; noterm=true;;
yap) ext=.dvi; run=xdvi; noterm=true;; bash) ext=;; *) ext=.ftx;; esac
if test "x$ext" != x; then filename=`winepath -u "$filename$ext"`; fi
if $noterm || tty --quiet; then "$run" "$filename" "$@"; echo Done.
else exec ${TERMINAL-xterm} -e "$0" --run-n-stop "$run" "$filename" "$@"; fi
END
chmod a+x ~/bin/ftexed-launch-cmd.sh

# Descend into windows/system dir
pushd ~/.wine/*/[Ww]indows/[Ss]ystem >/dev/null

# Create launcher helper binary that delegates to the launcher shell script
cat > ftexed-launch-helper.c <<\END
#include <unistd.h>
int main (int argc, char **argv) {
execlp ("ftexed-launch-cmd.sh", argv[0], argv[0], argv[1], NULL);
return 127; }
END
make ftexed-launch-helper > /dev/null

# Symlink dvips.exe and yap.exe to the launcher helper
ln -s -f ftexed-launch-helper dvips.exe
ln -s -f ftexed-launch-helper yap.exe

# Create launcher batch files
echo '@echo off' > goftex.bat
echo '%3' >> goftex.bat
echo 'cd %1' >> goftex.bat
echo -n 'bash ftexed-launch-cmd.sh ' >> goftex.bat
cp goftex.bat convert.bat
cp goftex.bat fmakeindex.bat
cp goftex.bat ftx2unicode.bat
echo 'ftex %2' >> goftex.bat
echo 'ftx2tex %2' >> convert.bat
echo 'fmakeidx %2' >> fmakeindex.bat
echo 'bash -c "echo ftx2unicode not available yet; false"' >> ftx2unicode.bat

# Pop back where we were (repeat three times!)
popd > /dev/null
