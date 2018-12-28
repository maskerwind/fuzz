#for filename in $(ls ./out/crashes/ | head -n -2)
#do 
#	afl-tmin -i ./out/crashes/$filename -o ./out/crashes/minimized/$filename ./sint
#done

for filename in $(ls ./out/crashes/minimized/)
do
	cat ./out/crashes/minimized/$filename
	printf "\n\n"
done
