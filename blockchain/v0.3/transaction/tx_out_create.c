#include "transaction.h"

/**
 * tx_out_create - new transaction
 * @amount: amount
 * @pub: pk
 * Return: pointer
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *tx_n = calloc(1, sizeof(*tx_n));

	if (!tx_n)
		return (NULL);

	tx_n->amount = amount;

	memcpy(tx_n->pub, pub, sizeof(tx_n->pub));
	if (!sha256((int8_t const *)tx_n, sizeof(tx_n->amount) + sizeof(tx_n->pub), tx_n->hash))
		return (free(tx_n), NULL);

	return (tx_n);

}
