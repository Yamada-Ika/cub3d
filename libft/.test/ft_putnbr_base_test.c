#include "../libft.h"
#include <stdio.h>

void run_ft_putnbr_base_test(void) {
	int n;

	n = 100;
	ft_putnbr_base(n, "0123456789");
	printf("\n%d\n", n);

	n = -100;
	ft_putnbr_base(n, "0123456789");
	printf("\n%d\n", n);

	n = 1234;
	ft_putnbr_base(n, "0123456789abcdef");
	printf("\n%x\n", n);

	n = -1234;
	ft_putnbr_base(n, "0123456789abcdef");
	printf("\n%x\n", n);

	n = 1234;
	ft_putnbr_base(n, "0123456789ABCDEF");
	printf("\n%X\n", n);

	n = -1234;
	ft_putnbr_base(n, "0123456789ABCDEF");
	printf("\n%X\n", n);
}

int main(void) {
	run_ft_putnbr_base_test();
	return (0);
}
