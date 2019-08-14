#!/bin/sh
echo please wait... counting lines
printf " *** LINE COUNTER *** \n\n" > line_count.txt
printf " -- LINES OF CODE -- \n" >> line_count.txt
svn ls -R | sed 's/\r$//g' | grep -e ".*\/$" -v| grep -e "^.*\.c$" | xargs svn blame -r 3:HEAD > all_lines.c
gcc -E ./all_lines.c | gawk "!/((^[\r\n\t\f\v ]*)([0-9]*)( )([^ \n]*)([\r\n]*))([\r\n\t\f\v ]*[{}][\r\n\t\f\v ]*$)|((^[\r\n\t\f\v ]*)([0-9]*)( *)([^ \n]*)([\r\n]*)$)([ \r\n\t\f\v]*$)|(^\#.*$)|(^[\r\n]*$)/" | gawk '{count[$2]++}END{for(j in count) if (j ~ /\./){ printf"%9s  %s\n", count[j], j}}' | /usr/bin/sort -rn >> line_count.txt

printf "\n -- COMMENT COUNT -- \n" >> line_count.txt
gawk "!/((^[ ]*)([0-9]*)( *)([^ \n0-9]{1,})([\r\n]*))( )([^\/\n\r\v\f]*)([^ \/\n\r\t\f\v])([^\/\n\r\v\f]*)(\/)(.*)(\/\/)|((^[ ]*)([0-9]*)( *)([^ \n0-9]{1,})([\r\n]*))( )([^\/\n\r\v\f]*)([^ \/\n\r\t\f\v])([^\/\n\r\v\f]*)(\/\/)|((^[ ]*)([0-9]*)( *)([^ \n0-9]{1,})([\r\n]*))( )([^\/\n\r\v\f\*]*)([^ \/\n\r\t\f\v])([^\/\n\r\v\f]*)(\/\*)([^\/\n\r\v\f\*]*)(\*\/)|((^[ ]*)([0-9]*)( *)([^ \n0-9]{1,})([\r\n]*))( )([^\/\n\r\v\f\*]*)([^ \/\n\r\t\f\v])([^\/\n\r\v\f]*)(\/)(.*)(\/\*)([^\/\n\r\v\f\*]*)(\*\/)/" all_lines.c > temp.c

gcc -E ./temp.c -o preproccessed.txt
diff --changed-group-format='%<%>' --unchanged-group-format='' -w preproccessed.txt temp.c | gawk '!/((^[ ]*)([0-9]*)( *)([^ \n]*)([\r\n]*))([ \r\n\t\f\v]*$)|(^\#.*$)/' | gawk '{count[$2]++}END{for(j in count) if (j ~ /\./){printf "%9s  %s\n", count[j], j}}' | /usr/bin/sort -rn >> line_count.txt

rm temp.c
rm all_lines.c
rm preproccessed.txt

cat line_count.txt
printf "\n\n"
read -p "Press any key to exit... " -n1 -s