if [[ $# -eq 1 ]]; then
  g++ src/main.cpp -o peer -pthread -std=c++20
  echo $1 | ./peer
  rm -f peer
else
  echo "Devi inserire la porta per avviare il server"
fi
