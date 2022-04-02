#include "../libft.h"

void run_ft_free_s_test(void) {
	char *str = strdup("hello");
	ft_free_s((void **)&str);
	if (str == NULL && malloc_size(str) == 0)
		printf("OK!\n");
	else
	{
		printf("KO!\n");
		free(str);
	}
}

int main(void) {
	run_ft_free_s_test();
	return (0);
}