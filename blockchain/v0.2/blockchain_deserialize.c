#include "blockchain.h"

#define CNUP (free(chain), close(fd))
#define CNUP_B (free(block), llist_destroy(list, 1, NULL))
#define ENDI(x) (endi ? SWAPENDIAN(x) : (void)0)
llist_t *deserialize_blocks(int fd, uint32_t len, uint8_t endi);
/**
 * blockchain_deserialize - deser
 * @path: path
 * Return: pointer
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	int fd;
	blockchain_t *chain = NULL;
	uint8_t endi;
	char buf[4096] = {0};
	uint32_t len;

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, buf, strlen("HBLK")) != strlen("HBLK") ||
		strcmp(buf, "HBLK"))
		return (CNUP, NULL);
	buf[strlen("0.2")] = 0;
	if (read(fd, buf, strlen("0.2")) != strlen("0.2") ||
		strcmp(buf, "0.2"))
		return (CNUP, NULL);
	chain = calloc(1, sizeof(*chain));
	if (!chain)
		return (CNUP, NULL);
	if (read(fd, &endi, 1) != 1)
		return (CNUP, NULL);

	endi = endi != _get_endianness();
	if (read(fd, &len, 4) != 4)
		return (CNUP, NULL);
	ENDI(len);
	chain->chain = deserialize_blocks(fd, len, endi);
	if (!chain)
		return (CNUP, NULL);
	return (close(fd), chain);

}

/**
 * deserialize_blocks - deser
 * @fd: fd
 * @len: len
 * @endi: endi
 * Return: pointer
 */
llist_t *deserialize_blocks(int fd, uint32_t len, uint8_t endi)
{
	block_t *block;
	llist_t *list = llist_create(MT_SUPPORT_TRUE);
	uint32_t i = 0;

	if (!list)
		return (NULL);
	for (i = 0; i < len; i++)
	{
		block = calloc(1, sizeof(*block));
		if (!block)
			return (CNUP_B, NULL);
		if (read(fd, &(block->info), sizeof(block->info)) != sizeof(block->info))
			return (CNUP_B, NULL);

		ENDI(block->info.index);
		ENDI(block->info.difficulty);
		ENDI(block->info.timestamp);
		ENDI(block->info.nonce);
		if (read(fd, &(block->data.len), 4) != 4)
			return (CNUP_B, NULL);
		ENDI(block->data.len);
		if (read(fd, block->data.buffer, block->data.len) != block->data.len)
			return (CNUP_B, NULL);
		if (read(fd, block->hash, SHA256_DIGEST_LENGTH) !=
			SHA256_DIGEST_LENGTH)
			return (CNUP_B, NULL);
		if (llist_add_node(list, block, ADD_NODE_REAR))
			return (CNUP_B, NULL);
	}
	return (list);

}
