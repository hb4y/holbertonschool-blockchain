#include "hblk_crypto.h"

/**
 * ec_create - create key
 * Return: pointer
 */
EC_KEY *ec_create(void)
{
	EC_KEY *key  = NULL;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);
	if (!(EC_KEY_generate_key(key)))
		return (NULL);

	return (key);
}
