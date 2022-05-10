#include "libft_test.h"

void run_ft_itoa_base_test(void) {
	char *num;
	int random;

	for (int i = 0; i < 10; i++) {
		random = (int)((rand() / (double)RAND_MAX - 0.5) * 2 * INT_MAX);
		num = ft_itoa_base(random, "0123456789");
		printf("expected : %d\n", random);
		printf("result   : %s\n", num);
		free(num);
	}

	for (int i = 0; i < 10; i++) {
		random = (int)((rand() / (double)RAND_MAX - 0.5) * 2 * INT_MAX);
		num = ft_itoa_base(random, "0123456789abcdef");
		printf("expected : %x\n", random);
		printf("result   : %s\n", num);
		free(num);
	}

	for (int i = 0; i < 10; i++) {
		random = (int)((rand() / (double)RAND_MAX - 0.5) * 2 * INT_MAX);
		num = ft_itoa_base(random, "0123456789ABCDEF");
		printf("expected : %X\n", random);
		printf("result   : %s\n", num);
		free(num);
	}
}

int main(void) {
	run_ft_itoa_base_test();
	return (0);
}
