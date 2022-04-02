#include "libft_test.h"

void run_ft_ultoa_base_test(void) {
	char *num;
	unsigned long random;

	for (int i = 0; i < 10; i++) {
		random = (unsigned long)((rand() / (double)RAND_MAX) * ULONG_MAX);
		num = ft_ultoa_base(random, "0123456789");
		printf("%lu\n", random);
		printf("%s\n", num);
		free(num);
	}

	for (int i = 0; i < 10; i++) {
		random = (unsigned long)((rand() / (double)RAND_MAX) * ULONG_MAX);
		num = ft_ultoa_base(random, "0123456789abcdef");
		printf("%lx\n", random);
		printf("%s\n", num);
		free(num);
	}

	for (int i = 0; i < 10; i++) {
		random = (unsigned long)((rand() / (double)RAND_MAX) * ULONG_MAX);
		num = ft_ultoa_base(random, "0123456789ABCDEF");
		printf("%lX\n", random);
		printf("%s\n", num);
		free(num);
	}
	random = 0;
	num = ft_ultoa_base(random, "0123456789ABCDEF");
	printf("%lX\n", random);
	printf("%s\n", num);
	free(num);
}

int main(void) {
	run_ft_ultoa_base_test();
	return (0);
}
