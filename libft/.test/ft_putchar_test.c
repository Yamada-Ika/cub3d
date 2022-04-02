#include "../libft.h"

void run_ft_putchar_test(void) {
	for (int i = 0; i < 256; ++i) {
		ft_putchar(i);
		if ((i + 1) % 41 == 0)
			putchar('\n');
	}
}

int main(void) {
	run_ft_putchar_test();
	return (0);
}
