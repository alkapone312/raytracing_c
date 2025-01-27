CC=cc
LIBS=libpng
CFLAGS="$(pkg-config $LIBS --cflags) -I./includes"
LIBS="$(pkg-config $LIBS --libs) -lm"

$CC $CFLAGS $(ls -lf ./src/*.c) -g -o raytracer $LIBS
