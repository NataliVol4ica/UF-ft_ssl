#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int		main()
{
	int		len;
	char	*str;
	char	*key;
	FILE	*plaintext;
	FILE	*script;

	// ======= GENERATING RANDOM STRING ==========
	plaintext = fopen("plaintext", "w");
	srand(time(NULL));   // should only be called once
	len = rand() % 255 + 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = 0; i < len; i++)
	{
		str[i] = rand() % 15;
		if (str[i] == 0)
			str[i] = rand() % 2 == 0 ? '\t' : '\n';
		else
			str[i] = rand() % 95 + 32;
	}
	str[len] = '\0';
	fprintf(plaintext, "%s", str);
	fclose(plaintext);
	
	// ========== GENERATING RANDOM KEY ============
	script = fopen("test.sh", "w");
	len = rand() % 16 + 1;
	key = (char*)malloc(sizeof(char) * (len + 1));
	key[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		key[i] = rand() % 16;
		key[i] = key[i] < 10 ? key[i] + '0' : key[i] - 10 + 'A' + (rand() % 2) * ('a' - 'A');
	}
	fprintf(script, "./ft_ssl des-ecb -i plaintext -o my_enc -k %s\n", key);
	fprintf(script, "openssl des-ecb -in plaintext -out ssl_enc -K %s\n", key);
	fprintf(script, "diff my_enc ssl_enc\n");
	fprintf(script, "./ft_ssl des-ecb -i ssl_enc -o my_dec -k %s\n", key);
	fprintf(script, "openssl des-ecb -in ssl_enc -out ssl_dec -K %s\n", key);
	fprintf(script, "diff my_dec ssl_dec\n");
	fclose(script);
	return (0);
}
