#!/bin/bash
#

function echoerr { echo "$@" >&2; }

export SERVICE_HOME=$(pwd)
if [ ! -e $SERVICE_HOME/bin/reposervice-env ]; then
	echoerr "\$SERVICE_HOME/bin/reposervice-env not found; suggest running $SERVICE_HOME/bin/reposervice-config"
	exit 1
fi

unset FOUND_NEWER_CONFIG
for configfile in $(find sed_templates -type f -print); do
	if [ $configfile -nt $SERVICE_HOME/bin/reposervice-env ]; then
		FOUND_NEWER_CONFIG="$FOUND_NEWER_CONFIG $configfile"
	fi
done

if [ ! -z "$FOUND_NEWER_CONFIG" ]; then
	echoerr "WARNING: Config files newer than reposervice-env found; running \$SERVICE_HOME/bin/reposervice-config is recommended:"
	echoerr " $FOUND_NEWER_CONFIG"
fi

source $SERVICE_HOME/bin/reposervice-env