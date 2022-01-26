#include "blockchain.h"

/**
 * block_destroy - free
 * @block: pointer
 */
void block_destroy(block_t *block)
{
	free(block);

}
