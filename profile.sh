#!/usr/bin/env bash

set -um
[ $# -gt 0 ] || { sed -n '2,/^#$/ s/^# //p' <"$0"; exit 1; }

pgid=`ps -o pgid= $$`

if [ $pgid = $(ps -o pgid= $(ps -o ppid= $$)) ]; then
    cmd=
    set -- "$0" "$@"
    for a; do cmd+="'${a//"'"/"'\\''"}' "; done
    exec bash -i -c "$cmd"
fi

case `uname` in
    Darwin|*BSD) sizes() { /bin/ps -o rss= -g $1; } ;;
    Linux) sizes() { /bin/ps -o rss= -$1; } ;;
    *) echo "`uname`: unsupported operating system" >&2; exit 2 ;;
esac

(
peak=0
while sizes=`sizes $pgid`
do
    set -- $sizes
    sample=$((${@/#/+}))
    let peak="sample > peak ? sample : peak"
    sleep 0.1
done
echo "memusg: peak=$peak" >&2
) &
monpid=$!


exec "$@"
