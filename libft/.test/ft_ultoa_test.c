#include "libft_test.h"

void run_ft_ultoa_test(void) {
	char *num;
	unsigned long random;

	for (int i = 0; i < 20; i++) {
		random = (unsigned long)((rand() / (double)RAND_MAX) * ULONG_MAX);
		num = ft_ultoa(random);
		printf("expected : %lu\n", random);
		printf("result   : %s\n", num);
		free(num);
	}
}

int main(void) {
	run_ft_ultoa_test();
	return (0);
}
