if [[ ! -d "build" ]]; then
    mkdir -p build
fi

function doStuff() {
    cd ./build
    cmake ..
    if [[ -f Makefile ]]; then
        make
    fi
}
doStuff
