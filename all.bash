#!/usr/bin/env bash

PLUGINS=BALEZverb

# Fow now, only a local VST3 install on Mac OSX is supported,
# packaging will come later. This script performs destructive
# operations on this directory, make sure it is made for this
# use. In case of doubt, do not edit it.
INSTALL_DIR=~/Library/Audio/Plug-Ins/VST3/BALEZ

# params: <message>
function ok {
    echo -e "\033[0;32;49m$@\\033[0m"
    return 0
}

# params: <message>
function ko {
    echo -e "\033[0;31;49mError: $@\\033[0m"
    return 1
}

# params: <message>
function title {
    echo -e "\033[0;32;40m$@\\033[0m\n"
    return 0
}

# params: <return_value> <message>
function warn-upon-failure {
    local ret=$1
    local msg=$2
    if [ $ret -ne 0 ]
    then
	ko "$msg"
    fi
    return $ret
}

# params: <command>
function be-quiet {
    $@ 2>&1 > /dev/null
    return $?
}

# params: <none>
function usage {
    echo -e "usage: $0 [help|build|clean|install]"
}

case $1 in

    "help")
	title "help for BALEZ suite"
	usage
	exit 0
	;;

    "build")
	title "building BALEZ suite"

	git submodule update --init --recursive

	for plugin in ${PLUGINS}; do
	    (
		ok "building ${plugin}"
		cd src/${plugin}
		cmake -B build && cmake --build build --config Release
	    )
	done

	exit 0
	;;

    "clean")
	title "cleaning BALEZ suite"

	rm -rf ${INSTALL_DIR}/*

	for plugin in ${PLUGINS}; do
	    (
		ok "cleaning ${plugin}"
		rm -rf src/${plugin}/build
	    )
	done

	exit 0
	;;

    "install")
	title "installing BALEZ suite"

	mkdir -p ${INSTALL_DIR}
	rm -rf ${INSTALL_DIR}/*

	for plugin in ${PLUGINS}; do
	    cp -r "$(find src/${plugin}/build -name '*.vst3')" ${INSTALL_DIR}/
	    ok "installed ${plugin}"
	done

	exit 0
	;;

esac

usage
exit 1
