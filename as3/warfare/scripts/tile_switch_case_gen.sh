offset=1000
tile_number=1024
file_name=output.txt

for i in $(seq 1 $tile_number); do
	counter=$((i + offset))
	echo -e "\t\t\t\tcase ConstTileset$offset"."TILE$counter""_ID:\r" >> $file_name
done

echo Done!