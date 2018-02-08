key=$1
iv=$2


# base64 enc
./ft_ssl base64 -i plaintext -o ./results/my_base64_e -e
openssl base64 -in plaintext -out ./results/ssl_base64_e -e
diff ./results/my_base64_e ./results/ssl_base64_e > temp
sh diff_check.sh "base64 encryption"

# base64 dec
./ft_ssl base64 -i ./results/ssl_base64_e -o ./results/my_base64_d -d
openssl base64 -in ./results/ssl_base64_e -out ./results/ssl_base64_d -d
diff ./results/my_base64_d ./results/ssl_base64_d > temp
sh diff_check.sh "base64 decryption"

# des-ecb enc
./ft_ssl des-ecb -i plaintext -o ./results/my_desecb_enc -k $key -e
openssl des-ecb -in plaintext -out ./results/ssl_desecb_enc -K $key -e
diff ./results/my_desecb_enc ./results/ssl_desecb_enc > temp
sh diff_check.sh "des-ecb encryption"

# des-ecb dec
./ft_ssl des-ecb -i ./results/ssl_desecb_enc -o ./results/my_desecb_dec -k $key
openssl des-ecb -in ./results/ssl_desecb_enc -out ./results/ssl_desecb_dec -K $key
diff ./results/my_desecb_dec ./results/ssl_desecb_dec > temp
sh diff_check.sh "des-ecb decryption"

# des-cbc enc
./ft_ssl des-cbc -i plaintext -o ./results/my_descbc_enc -k $key -v $iv -e
openssl des-cbc -in plaintext -out ./results/ssl_descbc_enc -K $key -iv $iv -e
diff ./results/my_descbc_enc ./results/ssl_descbc_enc > temp
sh diff_check.sh "dec-cbc encryption"

# des-cbc dec
./ft_ssl des-cbc -i ./results/ssl_descbc_enc -o ./results/my_descbc_dec -k $key -v $iv -d
openssl des-cbc -in ./results/ssl_descbc_enc -out ./results/ssl_descbc_dec -K $key -iv $iv -d
diff ./results/my_descbc_dec ./results/ssl_descbc_dec > temp
sh diff_check.sh "dec-cbc decryption"
