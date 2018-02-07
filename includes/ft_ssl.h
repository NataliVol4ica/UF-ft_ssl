/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:37:40 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/22 14:37:40 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "structs.h"
# include "libft.h"

t_str		*read_input(t_params *p);

/*
** DES
*/

void		des_ecb(void *param);
void		des_cbc(void *param);

t_str		*des_str_processing(t_params *p, t_str *str);

void		key_processing(t_params *p, t_des *des);
void		proceed_des_mode_pre(t_des_m mode, t_des *des, _Bool enc);
void		proceed_des_mode_final(t_des_m mode, t_des *des, _Bool enc);

void		des_str_to_bits(t_des *d, char *str);
void		des_key_to_bits(char *str, t_bits *b);
void		des_bits_to_str(t_des *d, char *str);

void		des_data_halv(t_des *des);
void		des_xor(t_bits *a, t_bits *b, size_t until);

void		des_key_permutation(t_des *des);
void		des_key_shift_enc(t_des *des);
void		des_key_shift_dec(t_des *des);
void		des_compression_permutation(t_des *des);

void		des_initial_permutation(t_des *des);
void		des_expand_permut(t_des *des);
void		des_sbox_perm(t_des *des, size_t num);
void		des_pbox_permutation(t_des *des);
void		des_final_permutation(t_des *des);

/*
** BASE64
*/

void		base64(void *param);

t_str		*base64_encrypt(t_str *str);
t_str		*base64_decrypt(t_str *str);

void		x8_to_x6(t_read *reader);
void		x6_to_x8(t_read *reader);

/*
** FLAG PARSING
*/

void		base64_parse_flags(t_params *p);
void		des_parse_flags(t_params *p, size_t i);

/*
** STRUCT TOOLS
*/

t_params	*new_param(int ac, char **av);
void		print_bits(t_bits bits, size_t len);

/*
** ERRORS
*/

void		malloc_error(void);
void		invalid_flag(char *str);
void		open_error(char *str);
void		key_error(void);
void		des_block_error(void);
void		base64_block_error(void);

#endif
