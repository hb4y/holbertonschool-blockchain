#include "hblk_crypto.h"

/**
 * ec-sign - sign
 * @key: key
 * @msg: string
 * @msglen: len
 * @sig: address
 * Return: pointer
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
				size_t msglen, sig_t *sig)
{
	uint32_t l = 0;

	if (!key || !msg || !msglen)
	{
		return (NULL);
	}
	bzero(sig->sig, sizeof(sig->sig));
	if (!ECDSA_sign(0, msg, msglen, sig->sig, &l, (EC_KEY *)key))
	{
		sig->len = 0;
		return (NULL);
	}
	sig->len = (uint8_t)l;
	return ((uint8_t *)sig->sig);
}
