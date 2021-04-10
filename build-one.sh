#!/bin/bash -ex

export CC=$CC_RAW
WORKDIR=$(realpath -m $WORKDIR)
PREFIX=${WORKDIR}/prefix
CFLAGS="${CFLAGS} -I${PREFIX}/include -DMUSL_P2ALIGN=${MUSL_P2ALIGN}"
echo ${CFLAGS}
echo ${WORKDIR}
echo ${PREFIX}
SRC=${PWD}

mkdir -p ${WORKDIR}
cd ${WORKDIR}
make distclean || true
rm -fr $PREFIX
mkdir -p $PREFIX
cp ${PRIVBOX_KERN_HEADERS}/include/ $PREFIX -ap
${SRC}/configure --enable-static --prefix=$PREFIX --target x86_64-linux
make -j28
make install
