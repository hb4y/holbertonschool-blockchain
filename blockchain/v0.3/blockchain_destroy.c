#include "blockchain.h"

/**
 * blockchain_destroy - free
 * @blockchain: pointer
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->chain, 1, (void (*)(llist_node_t))block_destroy);

	free(blockchain);

}
