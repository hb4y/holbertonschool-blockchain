#include "hblk_crypto.h"

/**
 * ec_load - load key
 * @folder: folder
 * Return: pointer
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *descriptor;
	char c_dir[256];
	EC_KEY *k = NULL;

	if (!folder)
		return (NULL);

	sprintf(c_dir, "%s/%s", folder, PUB_FILENAME);
	descriptor = fopen(c_dir, "r");
	if (!descriptor)
	{
		return (NULL);
	}
	if (!PEM_read_EC_PUBKEY(descriptor, &k, NULL, NULL))
	{
		fclose(descriptor);
		return (NULL);
	}
	fclose(descriptor);
	sprintf(c_dir, "%s/%s", folder, PRI_FILENAME);
	descriptor = fopen(c_dir, "r");
	if (!descriptor)
	{
		EC_KEY_free(k);
		return (NULL);
	}
	if (!PEM_read_ECPrivateKey(descriptor, &k, NULL, NULL))
	{
		EC_KEY_free(k);
		fclose(descriptor);
		return (NULL);
	}
	fclose(descriptor);

	return (k);
}
