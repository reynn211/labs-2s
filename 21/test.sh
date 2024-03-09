PREFIX="copy_"
DIRECTORY="."

help() {
  echo "Использование: test.sh [ОПЦИИ]"
  echo "  --prefix PREFIX   Установить префикс для файлов резервного копирования (по умолчанию: copy_)"
  echo "  --directory DIR   Установить директорию для поиска файлов (по умолчанию: .)"
  echo "  ?                 Показать это сообщение и выйти"
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prefix)
      PREFIX="$2"
      shift 2
      ;;
    --directory)
      DIRECTORY="$2"
      shift 2
      ;;
    ?)
      help
      exit 0
      ;;
    *)
      echo "Неизвестная опция: $1"
      help
      exit 1
      ;;
  esac
done

FILES=$(ls -l $DIRECTORY | grep -E "^[-rwx]{5}-[-rwx]{2}-[-rwx]" | awk '{print $9}')
for FILE in $FILES; do
  cp $DIRECTORY/$FILE $DIRECTORY/$PREFIX$FILE
  chmod ugo+w $DIRECTORY/$PREFIX$FILE
done
