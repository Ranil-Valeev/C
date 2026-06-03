#!/bin/bash

if [$# -ne 3]; then
    echo "Использование: $0 <путь> <что заменить> <замена>"
    exit 1
fi

file_path=$1 #путь к файлу
string_to_replace=$2 #строка, которую нужно заменить
replacement=$3 #замена

# замена строки
sed -i "" "s/$string_to_replace/$replacement/g" "$file_path"

echo "замена выполнена в файле $file_path"

file_size=$(stat -f%z < "$file_path")
current_date=$(date "+%Y-%m-%d %H:%M")
sha256=$(shasum -a 256 < "$file_path")
file="files.log"
echo 'src/'$file_path '-' $file_size '-' $current_date '-' $sha256 'sha256' >> "$file"