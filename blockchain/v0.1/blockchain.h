#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../../crypto/hblk_crypto.h"
#include "provided/endianness.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <llist.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <openssl/sha.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

/**
 * struct block_info_s - Block info structure
 *
 * @index:	  Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:	  Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */
typedef struct block_info_s
{
	/*
	 * The order of the elements in this structure should remain the same.
	 * It was designed so every element of this structure is aligned and
	 * doesn't require padding from the compiler.
	 * Therefore, it is possible to use the structure as an array of char,
	 * on any architecture.
	 */
	uint32_t	index;
	uint32_t	difficulty;
	uint64_t	timestamp;
	uint64_t	nonce;
	uint8_t	 prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

#define BLOCKCHAIN_DATA_MAX 1024

/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:	Data size (in bytes)
 */
typedef struct block_data_s
{
	/*
	 * @buffer must stay first, so we can directly use the structure as
	 * an array of char
	 */
	int8_t	  buffer[BLOCKCHAIN_DATA_MAX];
	uint32_t	len;
} block_data_t;

/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
	block_info_t	info; /* This must stay first */
	block_data_t	data; /* This must stay second */
	uint8_t	 hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain: Linked list of pointers to block_t
 */
typedef struct blockchain_s
{
	llist_t	 *chain;
} blockchain_t;


blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev,
	int8_t const *data, uint32_t data_len);

#endif
