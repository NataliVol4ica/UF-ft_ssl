./ft_ssl base64 -i plaintext -o ./results/my_base64_e
openssl base64 -in plaintext -out ./results/ssl_base64_e
diff ./results/my_base64_e ./results/ssl_base64_e
./ft_ssl des-ecb -i plaintext -o ./results/my_desecb_enc -k 28A14
openssl des-ecb -in plaintext -out ./results/ssl_desecb_enc -K 28A14
diff ./results/my_desecb_enc ./results/ssl_desecb_enc
./ft_ssl des-ecb -i ./results/ssl_desecb_enc -o ./results/my_desecb_dec -k 28A14
openssl des-ecb -in ./results/ssl_desecb_enc -out ./results/ssl_desecb_dec -K 28A14
diff ./results/my_desecb_dec ./results/ssl_desecb_dec
