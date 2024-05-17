NAME="shadertoh"
MODE=$1

CFLAGS="-std=c17 -O2"
CFLAGS_D="-std=c17 -O0 -g -fsanitize=address -fsanitize=undefined"

if [[ $MODE == "d" ]]
then
  pushd debug
  cc ../src/*.c ../src/base/*.c $CFLAGS_D -o $NAME
 `` ./$NAME
  popd
else
  cc src/*.c src/base/*.c $CFLAGS -o $NAME
  mv -f $NAME ~/bin/
fi
