#include "hblk_crypto.h"

/**
 * ec_to_pub - get public k
 * @key: pointer
 * @pub: public key
 * Return: public key
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	BN_CTX *seed = NULL;
	const EC_GROUP *g = NULL;
	const EC_POINT *p = NULL;

	if (key == NULL)
		return (NULL);

	seed = BN_CTX_new();
	g = EC_KEY_get0_group(key);
	p = EC_KEY_get0_public_key(key);
	EC_POINT_point2oct(g, p,
			(point_conversion_form_t) POINT_CONVERSION_UNCOMPRESSED,
			(unsigned char *) pub, EC_PUB_LEN, seed);
	BN_CTX_free(seed);

	return (pub);
}
