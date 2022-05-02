#!/bin/sh

echo "number of args: $#"

if [ $# -ge 2]; then
	while [ $# -gt 0 ]; do
		dir = $1
		file = $2
		/// process
		if [ -d "$dir" ]; then
			if [ -r "$dir/$file" ]; then

			fi
		else
			echo "$dir is not a directory"
			exit 1
		fi
		shift 2
	done
fi
