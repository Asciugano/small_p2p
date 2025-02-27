if [[ $# -ne 2 ]]; then
  echo "Devi inserire messaggio e porta"
  echo "./mess.sh 'ciao come stai' 5001"
  exit 1
fi

echo $1 | nc 127.0.0.1 $2
