#!/bin/bash
if [ -f /proc/proctest/rw ]; then
    echo "$@" > /proc/proctest/rw
    cat /proc/proctest/rw
fi
