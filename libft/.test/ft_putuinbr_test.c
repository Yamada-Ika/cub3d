#include "../libft.h"

void run_ft_putuinbr_test(void) {
	ft_putuinbr(UINT_MAX);
	printf("\n%u\n", UINT_MAX);
	ft_putuinbr(4294967296);
	printf("\n%u\n", 4294967296);
}

int main(void) {
	run_ft_putuinbr_test();
	return (0);
}
