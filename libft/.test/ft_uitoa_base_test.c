#include "libft_test.h"

void run_ft_uitoa_base_test(void) {
	char *num;
	unsigned int random;

	for (unsigned int i = 0; i < 10; i++) {
		random = (unsigned int)((rand() / (double)RAND_MAX) * UINT_MAX);
		num = ft_uitoa_base(random, "0123456789");
		printf("expected : %u\n", random);
		printf("result   : %s\n", num);
		free(num);
	}

	for (unsigned int i = 0; i < 10; i++) {
		random = (unsigned int)((rand() / (double)RAND_MAX) * UINT_MAX);
		num = ft_uitoa_base(random, "0123456789abcdef");
		printf("expected : %x\n", random);
		printf("result   : %s\n", num);
		free(num);
	}

	for (unsigned int i = 0; i < 10; i++) {
		random = (unsigned int)((rand() / (double)RAND_MAX) * UINT_MAX);
		num = ft_uitoa_base(random, "0123456789ABCDEF");
		printf("expected : %X\n", random);
		printf("result   : %s\n", num);
		free(num);
	}
}

int main(void) {
	run_ft_uitoa_base_test();
	return (0);
}
