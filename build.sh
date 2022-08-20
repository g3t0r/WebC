mkdir -p build
cc src/main.c src/tcp.c src/files.c src/http.c src/server.c -o ./build/webc
