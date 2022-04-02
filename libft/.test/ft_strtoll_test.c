#include "../libft.h"
#include <assert.h>
#include <stdio.h>

void run_ft_strtoll_test(void) {
	long long	ft_result;
	long long	lib_result;
	char		*ft_s;
	char		*lib_s;

	for (int i = 0; i < 35; i++) {
		ft_result = ft_strtoll("123", &ft_s, i);
		lib_result = strtoll("123", &lib_s, i);
		printf("base : %d\n", i);
		printf("ft   : %lld\n", ft_result);
		printf("lib  : %lld\n", lib_result);
		assert(ft_result == lib_result);
		assert(!ft_strcmp(ft_s, lib_s));
	}
}

int main(void) {
	run_ft_strtoll_test();
	return (0);
}
