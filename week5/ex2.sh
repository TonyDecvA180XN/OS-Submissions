# this is our mutex
lockdir=/tmp/myscript.lock

for i in {1..10}
do
    while : # wait until mutex is unlocked
    do
        if mkdir "$lockdir" &> /dev/null
        then
            break
        else
            :
        fi
    done
    # file doesn't exist guard
    FILE=./numbers.txt
    if test -f "$FILE"; then
        NUMBER=$(tail -n 1 < numbers.txt)
        expr $NUMBER + 1 >> numbers.txt
    else
        echo "0" > numbers.txt
    fi
    # unlock mutex after using
    rm -r "$lockdir" &> /dev/null
done
