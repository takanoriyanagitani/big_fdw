#!/bin/bash

NAME=s1_fdw
PV=12
V=1.0

LIB_DIR=/usr/lib/postgresql/${PV}/lib
CNF_DIR=/usr/share/postgresql/${PV}/extension

build(){
  cmake .
  cmake --build .
}

install(){
  ln --verbose --force ./${NAME}.so        ${LIB_DIR}/
  ln --verbose --force ./${NAME}.control   ${CNF_DIR}/
  ln --verbose --force ./${NAME}--${V}.sql ${CNF_DIR}/
}

check(){
  psql --file ./${NAME}.test.sql
}

build && install && check
