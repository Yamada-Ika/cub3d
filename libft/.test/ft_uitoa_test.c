#include "../libft.h"

void run_ft_uitoa_test(void) {
	unsigned int random;
	char *ret;
	for (unsigned int i = 0; i < 20; ++i) {
		random = (unsigned int)(rand() / (double)RAND_MAX * UINT_MAX);
		ret = ft_uitoa(random);
		printf("%u = %s\n", random, ret);
		free(ret);
	}
}

int main(void) {
	run_ft_uitoa_test();
	return (0);
}