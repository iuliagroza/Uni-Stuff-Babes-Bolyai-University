#!/bin/sh

if test $# -eq 1; then
	if test -r $1; then
		if file $1|grep -q ":.*text"; then
			#grep "^[a-z].*[A-Z]$" $1
			#awk '{if (match($0, "^[a-z]") && match($0, "[A-Z]$")) print $0}' $1
			awk '{split($0, a, ""); 
			n = length(a);
			if (n>2 && tolower(a[1])==a[1] && toupper(a[n])==a[n]) {
		       	      	print length(a) " " length($0) " " $0;
			}
			}' $1
		fi
	fi
else	
	echo "Usage: $0 textFile"
	exit 1
fi
