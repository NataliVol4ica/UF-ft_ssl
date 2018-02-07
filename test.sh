./ft_ssl des-ecb -i plaintext -o my_res -k 74Aef3Da5FB6DaD
openssl des-ecb -in plaintext -out ssl_res -K 74Aef3Da5FB6DaD
diff my_res ssl_res
