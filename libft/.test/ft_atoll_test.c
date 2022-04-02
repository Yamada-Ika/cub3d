#include "../libft.h"
#include <assert.h>
#include <stdio.h>

void run_ft_atoll_test(void) {
	long long	ft_result;
	long long	lib_result;

	ft_result = ft_atoll("123");
	lib_result = atoll("123");
	assert(ft_result == lib_result);

	ft_result = ft_atoll("122303303002202");
	lib_result = atoll("122303303002202");
	assert(ft_result == lib_result);
}

int main(void) {
	run_ft_atoll_test();
	return (0);
}
