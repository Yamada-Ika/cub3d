#include "../libft.h"

void run_ft_strcmp_test(void) {
	char *s1 = strdup("hi");
	char *s2 = strdup("world");

	if (ft_strcmp(s1, s2) != strcmp(s1, s2))
	{
		printf("KO!\n");
		return ;
	}
}

int main(void) {
	run_ft_strcmp_test();
	return (0);
}
