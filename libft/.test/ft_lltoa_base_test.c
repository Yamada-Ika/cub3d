#include "libft_test.h"

void run_ft_lltoa_base_test(void) {
	char *num;
	long long random;

	for (int i = 0; i < 10; i++) {
		random = (long long)((rand() / (double)RAND_MAX - 0.5) * 2 * LLONG_MAX);
		num = ft_lltoa_base(random, "0123456789");
		printf("%lld\n", random);
		printf("%s\n", num);
		free(num);
	}

	for (int i = 0; i < 10; i++) {
		random = (long long)((rand() / (double)RAND_MAX - 0.5) * 2 * LLONG_MAX);
		num = ft_lltoa_base(random, "0123456789abcdef");
		printf("%llx\n", random);
		printf("%s\n", num);
		free(num);
	}

	for (int i = 0; i < 10; i++) {
		random = (long long)((rand() / (double)RAND_MAX - 0.5) * 2 * LLONG_MAX);
		num = ft_lltoa_base(random, "0123456789ABCDEF");
		printf("%llX\n", random);
		printf("%s\n", num);
		free(num);
	}
}

int main(void) {
	run_ft_lltoa_base_test();
	return (0);
}
