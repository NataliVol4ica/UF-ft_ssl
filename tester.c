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

	plaintext = fopen("plaintext", "w");
	script = fopen("test.sh", "w");

	// ======= GENERATING RANDOM STRING ==========
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
	
	// ========== BASE64 =============

	fprintf(script, "./ft_ssl base64 -i plaintext -o ./results/my_base64_e\n");
	fprintf(script, "openssl base64 -in plaintext -out ./results/ssl_base64_e\n");
	fprintf(script, "diff ./results/my_base64_e ./results/ssl_base64_e\n");

	// ========== GENERATING RANDOM KEY ============
	len = rand() % 16 + 1;
	key = (char*)malloc(sizeof(char) * (len + 1));
	key[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		key[i] = rand() % 16;
		key[i] = key[i] < 10 ? key[i] + '0' : key[i] - 10 + 'A' + (rand() % 2) * ('a' - 'A');
	}
	fprintf(script, "./ft_ssl des-ecb -i plaintext -o ./results/my_desecb_enc -k %s\n", key);
	fprintf(script, "openssl des-ecb -in plaintext -out ./results/ssl_desecb_enc -K %s\n", key);
	fprintf(script, "diff ./results/my_desecb_enc ./results/ssl_desecb_enc\n");
	fprintf(script, "./ft_ssl des-ecb -i ./results/ssl_desecb_enc -o ./results/my_desecb_dec -k %s\n", key);
	fprintf(script, "openssl des-ecb -in ./results/ssl_desecb_enc -out ./results/ssl_desecb_dec -K %s\n", key);
	fprintf(script, "diff ./results/my_desecb_dec ./results/ssl_desecb_dec\n");
	fclose(script);
	return (0);
}
