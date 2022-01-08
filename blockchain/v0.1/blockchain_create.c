#include "blockchain.h"

#define GENESIS_DATA "Holberton School"
#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"

/**
 * blockchain_create - create
 * Return: pointer or null
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *n_bc = calloc(1, sizeof(*n_bc));
	block_t *n_b = calloc(1, sizeof(*n_b));
	llist_t *list = llist_create(MT_SUPPORT_TRUE);

	if (!n_bc || !n_b || !list)
	{
		free(n_bc), free(n_b), llist_destroy(list, 1, NULL);
		return (NULL);
	}

	n_b->info.timestamp = 1537578000;

	memcpy(&(n_b->data.buffer), GENESIS_DATA, 16);

	n_b->data.len = 16;

	memcpy(&(n_b->hash), GENESIS_HASH, SHA256_DIGEST_LENGTH);

	if (llist_add_node(list, n_b, ADD_NODE_FRONT))
	{
		free(n_bc), free(n_b), llist_destroy(list, 1, NULL);
		return (NULL);
	}
	n_bc->chain = list;

	return (n_bc);
}
