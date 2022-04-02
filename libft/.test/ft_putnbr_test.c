#include "../libft.h"
#include <stdio.h>

void run_ft_putnbr_test(void) {
	int random;
	for (int i = 0; i < 100; ++i) {
		random = RAND_MAX / 2 * (-1) + rand();
		printf(" = %d", random);
		ft_putnbr(random);
		putchar('\n');
	}
}

int main(void) {
	run_ft_putnbr_test();
	return (0);
}
