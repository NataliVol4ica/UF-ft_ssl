./ft_ssl base64 -i plaintext -o ./results/my_base64_e
openssl base64 -in plaintext -out ./results/ssl_base64_e
diff ./results/my_base64_e ./results/ssl_base64_e
./ft_ssl base64 -i ./results/ssl_base64_e -o ./results/my_base64_d
openssl base64 -in ./results/ssl_base64_e -out ./results/ssl_base64_d
diff ./results/my_base64_d ./results/ssl_base64_d
./ft_ssl des-ecb -i plaintext -o ./results/my_desecb_enc -k F
openssl des-ecb -in plaintext -out ./results/ssl_desecb_enc -K F
diff ./results/my_desecb_enc ./results/ssl_desecb_enc
./ft_ssl des-ecb -i ./results/ssl_desecb_enc -o ./results/my_desecb_dec -k F
openssl des-ecb -in ./results/ssl_desecb_enc -out ./results/ssl_desecb_dec -K F
diff ./results/my_desecb_dec ./results/ssl_desecb_dec
./ft_ssl des-cbc -i plaintext -o ./results/my_descbc_enc -k F -v 1
openssl des-cbc -in plaintext -out ./results/ssl_descbc_enc -K F -iv 1
diff ./results/my_descbc_enc ./results/ssl_descbc_enc
./ft_ssl des-cbc -i ./results/ssl_descbc_enc -o ./results/my_descbc_dec -k F -v 1
openssl des-cbc -in ./results/ssl_descbc_enc -out ./results/ssl_descbc_dec -K F -iv 1
diff ./results/my_descbc_dec ./results/ssl_descbc_dec
