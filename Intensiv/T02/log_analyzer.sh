#!/bin/bash
File=$1

if [ -z "$File" ]; then
  echo "Ошибка: не указан путь к файлу."
  exit 1
fi
if [ ! -f "$File" ]; then
  echo "Ошибка: файл '$file_path' не существует."
  exit 1
fi


total_record=$(wc -l < "$File")
number_unique=$(sort "$File" | uniq | wc -l)
calculate_hash() {
  sha256sum "$File" | cut -d ' ' -f 1
}
number_changes=$(calculate_hash)
changes=0

if [ -f "$hash_file" ]; then
  previous_hash=$(cat "$hash_file")
else
  previous_hash=""
fi

if [ "$number_changes" != "$previous_hash" ]; then
  changes=1
fi

echo "$total_record" "$number_unique" "$changes"
