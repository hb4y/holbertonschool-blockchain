#include "hblk_crypto.h"

/**
 * ec_verify - verify
 * @key: key
 * @msg: string
 * @msglen: len
 * @sig: sign
 * Return: 1 if verified
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen,
				sig_t const *sig)
{
	if (!key || !msg || !sig)
		return (0);
	return (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key) == 1);
}
