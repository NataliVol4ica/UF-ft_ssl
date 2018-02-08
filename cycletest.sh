#check input var
if [ "$#" -ne 1 ]
then
	echo "[ERROR]Invalid number of arguments. Needed one (number of tests)"
	exit
fi

#pre
unt=$1
((unt++))
rm fails
touch fails
echo "If the file is not empty, HAHAHHA LOH" > fails
count=0

make -C ./resources/ test

#main alg
for ((i = 1; i < unt; i++))
do
	printf $i"|"

	touch differ

	#one step of test
	key=`cat -n ./resources/files/key`
	iv=`cat -n ./resources/files/iv`
	./resources/tester
	sh ./resources/bash_scripts/test.sh $key $iv 
	err=`wc -l < differ`
	#if there is a difference
	if ! [ "$err" -eq "0" ]
	then
		((count++))
		echo " ===================== " >> fails
		printf ">>> TEXT \"" >> fails
		cat plaintext >> fails
		echo "\"" >> fails
		printf ">>> KEY = " >> fails
		cat key >>fails
		echo "" >> fails
		printf ">>> IV = " >> fails
		cat iv >>fails
		echo "" >> fails
		echo ">>> FAILED:" >> fails
		cat differ >>fails
		echo "" >> fails
	fi
	rm differ
done

# result print
if ! [ "$unt" -gt 1 ]
then
	exit
fi

echo ""
if ! [ "$count" -eq "0" ]
then
	echo '\033[0;31m'$count" FAILS!"'\033[0m'
else
	echo '\033[0;32m'"OK :)"'\033[0m'
fi
