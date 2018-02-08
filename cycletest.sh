rm fails
touch fails
echo "If the file is not empty, HAHAHHA LOH" > fails
for ((i = 1; i < 2; i++))
do
	echo $i

	touch differ

	key=`cat -n key`
	iv=`cat -n iv`
	make test
	./tester
	sh test.sh $key $iv #> silence
	err=`wc -l < differ`
	if ! [ "$err" -eq "0" ]
	then
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