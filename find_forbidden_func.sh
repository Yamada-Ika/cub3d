#!/bin/bash

set -u

# Find cub3d binary
if [ ! -f "cub3d" ]; then
	echo "[Info] Error: Not found cub3d executable file " 1>&2
	echo "       You must build cub3d before executing this script with make" 1>&2
	exit 1
fi

# Bonus part does not need to check
echo "[Info] Wait ! Checking functions are needed in only mandatory part !"
echo "       Make sure compile mandatory sources !"
echo "       If you want to continue to run this script ? [Y/n]"
while read buf; do
	if [[ "${buf}" == "n" || "${buf}" == "no" || "${buf}" == "N" || "${buf}" == "No" ]]; then
		exit 0
	fi
	if [[ "${buf}" == "Y" || "${buf}" == "Yes" || "${buf}" == "yes" || "${buf}" == "y" ]]; then
		break
	fi
	echo "[Info] Enter yes or no !"
done

if [[ "${buf}" == "" ]]; then
	exit 0
fi

# Allowed functions list
#   open, close, read, write,
#   printf, malloc, free, perror,
#   strerror, exit
#   cos, sin, acos, abs
allow_funcs=("open" "close" "read" "write" "printf" "malloc" "free" "perror" "strerror" "exit" "cos" "sin" "acos" "abs")

echo "[Info] You can use these functions : ${allow_funcs[@]}"

function is_func_in_allowed_funcs() {
	func=${1}
	for item in "${allow_funcs[@]}"; do
		if [[ "${func}" == "${item}" ]]; then
			return 1
		fi
	done
	return 0
}

for func in $(nm -u cub3d | grep "^_[a-z]" | tr -d '_'); do
	echo "[Info] Find ${func} in your cub3d"
	# Find fobidden function
	if [[ "$(is_func_in_allowed_funcs ${func}; echo $?)" == "0" ]]; then
		# Ignore fobidden function in minilibx
		grep -rnw 'libft' -e "${func}" | grep -v "//" > /dev/null
		libft_res=$(echo $?)
		grep -rnw 'src' -e "${func}" | grep -v "//" > /dev/null
		src_res=$(echo $?)
		if [[ ${libft_res} -eq 0 || ${src_res} -eq 0 ]]; then
			echo "[Info] Find : ${func}"
			echo "       This function is forbidden. Check below file !"
			grep -rnw 'libft' -e "${func}" | grep -v "//"
			grep -rnw 'src' -e "${func}" | grep -v "//"
			exit 1
		fi
		echo "[Info] No worry ! ${func} is in minilibx !"
		continue
	fi
	echo "[Info] No worry ! ${func} is allowed !"
done

echo "[Info] No fobidden functions in your cub3d !"
