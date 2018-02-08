./ft_ssl des-ecb -i plaintext -o my_enc -k E8Bf1a2
openssl des-ecb -in plaintext -out ssl_enc -K E8Bf1a2
echo ">>>>>>> diff 1"
diff my_enc ssl_enc
./ft_ssl des-ecb -i ssl_enc -o my_dec -k E8Bf1a2
openssl des-ecb -in ssl_enc -out ssl_dec -K E8Bf1a2
echo ">>>>>>> diff 2"
diff my_dec ssl_dec
