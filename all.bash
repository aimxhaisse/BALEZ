#!/usr/bin/env bash

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
    echo -e "\033[0;32;40m$@\\033[0m"
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
    echo -e "usage: $0 [help|build|install]"
}

case $1 in

    "help")
	usage
	exit 0
	;;

    "build")
	title "building VSTs"
	exit 0
	;;

    "install")
	title "installing VSTs"
	exit 0
	;;

esac

usage
exit 1
