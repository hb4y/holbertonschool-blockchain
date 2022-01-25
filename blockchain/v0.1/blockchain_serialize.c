#include "blockchain.h"

/**
 * blockchain_serialize - ser
 * @blockchain: pointer
 * @path: path
 * Return: 0 or 1
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	int fd, i, len_s;
	uint8_t endi = _get_endianness();

	if (!blockchain || !blockchain->chain || !path)
		return (-1);

	len_s = llist_size(blockchain->chain);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

	if (fd == -1)
		return (-1);
	if (write(fd, "HBLK", strlen("HBLK")) != strlen("HBLK"))
		return (close(fd), -1);
	if (write(fd, "0.1", strlen("0.1")) != strlen("0.1"))
		return (close(fd), -1);
	if (write(fd, &endi, 1) != 1)
		return (close(fd), -1);
	if (write(fd, &len_s, 4) != 4)
		return (close(fd), -1);

	for (i = 0; i < len_s; i++)
	{
		block_t *block = llist_get_node_at(blockchain->chain, i);

		if (!block)
			return (close(fd), -1);
		if (write(fd, &(block->info), sizeof(block->info)) != sizeof(block->info))
			return (close(fd), -1);
		if (write(fd, &(block->data.len), 4) != 4)
			return (close(fd), -1);
		if (write(fd, block->data.buffer, block->data.len) != block->data.len)
			return (close(fd), -1);
		if (write(fd, block->hash, SHA256_DIGEST_LENGTH) !=
			SHA256_DIGEST_LENGTH)
			return (close(fd), -1);
	}
	return (close(fd), 0);

}
