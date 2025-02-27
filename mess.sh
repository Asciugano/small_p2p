help() {
  echo "┌────────────────────────────────────────────────────────────────────────────────┐"
  echo "│./mess.sh [messaggio] [porta] <opzione>                                         │"
  echo "│./mess.sh [messaggio] [porta] <-c | --curl>   | Invia il messaggio tramite curl │"
  echo "└────────────────────────────────────────────────────────────────────────────────┘"
}

if [[ $# -eq 1 ]]; then
  if [[ $1 -eq "-h" || $1 == "--help" ]]; then
    help
  fi
fi

if [[ $# -lt 2 ]]; then
  echo "Devi inserire messaggio e porta"
  echo "guarda -h"
  exit 1
fi

if [[ $# -eq 2 ]]; then
  echo $1 | nc 127.0.0.1 $2
elif [[ $# -eq 3 ]]; then
  if [[ $3 == "-c" || $3 == "--curl" ]]; then
    curl -d "$1" 127.0.0.1:$2
  fi
fi
