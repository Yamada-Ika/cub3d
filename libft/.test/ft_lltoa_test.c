#include "../libft.h"

void run_ft_lltoa_test(void) {
	char *num;
	long long random;

	for (int i = 0; i < 20; i++) {
		random = (long long)((rand() / (double)RAND_MAX - 0.5) * 2 * LLONG_MAX);
		num = ft_lltoa(random);
		printf("%lld\n", random);
		printf("%s\n", num);
		free(num);
	}
}

int main(void) {
	run_ft_lltoa_test();
	return (0);
}
