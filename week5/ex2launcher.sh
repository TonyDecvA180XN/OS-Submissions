# mutex from last session removal
lockdir=/tmp/myscript.lock
rm -r "$lockdir" &> /dev/null

#starting two instances
./ex2.sh &
./ex2.sh
