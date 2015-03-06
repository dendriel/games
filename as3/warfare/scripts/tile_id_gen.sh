offset=1000
tile_number=1024
file_name=ConstTileset$offset.as

echo -e "package src.tiles.tileset$offset\r" >> $file_name
echo -e "{\r" >> $file_name

echo -e "\tpublic class ConstTileset$offset\r" >> $file_name
echo -e "\t{\r" >> $file_name


for i in $(seq 1 $tile_number); do
	counter=$((i + offset))
	echo -e "\t\tpublic static const TILE$counter""_ID:int = $counter;\r" >> $file_name
done

echo -e "\t}\r" >> $file_name
echo -e "}" >> $file_name

echo Done!