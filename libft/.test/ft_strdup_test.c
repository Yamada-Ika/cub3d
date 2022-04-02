#include "../libft.h"

void run_ft_strdup_test(void) {
	char *str1 = ft_strdup("hello, 42!");
	char *str2 = strdup("hello, 42!");

	if (strcmp(str1, str2) == 0 && (malloc_size(str1) == 16))
		printf("OK!\n");
	else
	{
		printf("Your ft_strdup has %zu\n", malloc_size(str1));
		printf("KO!\n");
	}
	free(str1);
	free(str2);
}

int main(void) {
	run_ft_strdup_test();
	return (0);
}