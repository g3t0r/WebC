mkdir -p build
cc src/tcp.c src/files.c src/http.c src/server.c -o ./build/webC
