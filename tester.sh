#!/bin/bash

# Gere uma mensagem com 10.000 palavras ("word0 word1 word2 ...")
MSG=$(seq 0 9999 | sed 's/.*/word&/' | tr '\n' ' ')

# Substitua com o PID atual do seu server
PID=$1

if [ -z "$PID" ]; then
    echo "Uso: ./test_minitalk.sh <PID_DO_SERVER>"
    exit 1
fi

# Enviar para o client
./client $PID "$MSG"
