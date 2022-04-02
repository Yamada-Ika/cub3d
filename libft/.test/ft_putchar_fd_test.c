#include "libft_test.h"

void run_ft_putchar_fd_test(void) {
	write(STDOUT_FILENO, "ft : ", 7);
	for (int i = -128; i < 256; ++i) {
		ft_putchar_fd(i, STDOUT_FILENO);
	}
	write(STDOUT_FILENO, "\n\n", 2);

	write(STDOUT_FILENO, "expected : ", 7);
	for (int i = -128; i < 256; ++i) {
		putchar(i);
	}
	write(STDOUT_FILENO, "\n\n", 2);
}

int main(void) {
	run_ft_putchar_fd_test();
	return (0);
}
