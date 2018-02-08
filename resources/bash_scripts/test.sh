key=$1
iv=$2
plaintext=./resources/files/plaintext
res=./resources/results
sc=./resources/bash_scripts

# base64 enc
./ft_ssl base64 -i $plaintext -o $res/my_base64_e -e
openssl base64 -in $plaintext -out $res/ssl_base64_e -e
diff $res/my_base64_e $res/ssl_base64_e > temp
sh $sc/diff_check.sh "base64 encryption"

# base64 dec
./ft_ssl base64 -i $res/ssl_base64_e -o $res/my_base64_d -d
openssl base64 -in $res/ssl_base64_e -out $res/ssl_base64_d -d
diff $res/my_base64_d $res/ssl_base64_d > temp
sh $sc/diff_check.sh "base64 decryption"

# des-ecb enc
./ft_ssl des-ecb -i $plaintext -o $res/my_desecb_enc -k $key -e
openssl des-ecb -in $plaintext -out $res/ssl_desecb_enc -K $key -e
diff $res/my_desecb_enc $res/ssl_desecb_enc > temp
sh $sc/diff_check.sh "des-ecb encryption"

# des-ecb dec
./ft_ssl des-ecb -i $res/ssl_desecb_enc -o 	$res/my_desecb_dec -k $key
openssl des-ecb -in $res/ssl_desecb_enc -out	$res/ssl_desecb_dec -K $key
diff $res/my_desecb_dec $res/ssl_desecb_dec > temp
sh $sc/diff_check.sh "des-ecb decryption"

# des-cbc enc
./ft_ssl des-cbc -i $plaintext -o $res/my_descbc_enc -k $key -v $iv -e
openssl des-cbc -in $plaintext -out $res/ssl_descbc_enc -K $key -iv $iv -e
diff $res/my_descbc_enc $res/ssl_descbc_enc > temp
sh $sc/diff_check.sh "dec-cbc encryption"

# des-cbc dec
./ft_ssl des-cbc -i $res/ssl_descbc_enc -o $res/my_descbc_dec -k $key -v $iv -d
openssl des-cbc -in $res/ssl_descbc_enc -out $res/ssl_descbc_dec -K $key -iv $iv -d
diff $res/my_descbc_dec $res/ssl_descbc_dec > temp
sh $sc/diff_check.sh "dec-cbc decryption"
