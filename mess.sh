if [[ $# -lt 2 ]]; then
  echo "Devi inserire messaggio e porta"
  echo "./mess.sh 'ciao come stai' 5001"
  exit 1
fi

if [[ $# -eq 2 ]]; then
  echo $1 | nc 127.0.0.1 $2
elif [[ $# -eq 3 ]]; then
  if [[ $3 == "-c" || $3 == "--curl" ]]; then
    curl -d "$1" 127.0.0.1:$2
  fi
fi
