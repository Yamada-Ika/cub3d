#include "../libft.h"

void run_ft_strstr_test(void) {
	char *s1 = strdup("Simpler is usually better");
	char *s2 = strdup("better");
	
	if (strcmp(ft_strstr(s1, s2), "better") != 0) {
		printf("KO!\n");
		return ;
	}
	free(s1);
	free(s2);

	s1 = strdup("better than better");
	s2 = strdup("better than better");
	
	if (strcmp(ft_strstr(s1, s2), "better than better") != 0) {
		printf("KO!\n");
		return ;
	}
	free(s1);
	free(s2);
}

int main(void) {
	run_ft_strstr_test();
	return (0);
}
