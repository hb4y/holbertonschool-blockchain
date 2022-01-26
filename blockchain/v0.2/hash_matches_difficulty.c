#include "blockchain.h"

/**
 * checker - check diff
 * @hash: buffer
 * Return: diff
 */
uint32_t checker(uint8_t const hash[SHA256_DIGEST_LENGTH])
{
	uint8_t *p = (uint8_t *)hash;
	uint32_t d = 0;
	int i;

	for (; p < hash + SHA256_DIGEST_LENGTH; p++)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*p >> i) & 1)
				return (d);
			d++;
		}
	}

	return (d);
}

/**
 * hash_matches_difficulty - match
 * @hash: buffer
 * @difficulty: diff
 * Return: 1 or 0
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
	uint32_t difficulty)
{
	if (!hash)
		return (0);

	if (checker(hash) >= difficulty)
		return (1);
	return (0);
}
