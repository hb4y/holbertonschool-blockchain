#include "hblk_crypto.h"

/**
* ec_save - save on file
* @key: key
* @folder: folder
* Return: 1
*/
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *descriptor;
	char c_dir[256];

	if (key == NULL || folder == NULL)
		return (0);

	mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	sprintf(c_dir, "%s/%s", folder, PRI_FILENAME);
	descriptor = fopen(c_dir, "w");
	if (!descriptor)
		return (0);
	if (!PEM_write_ECPrivateKey(descriptor, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(descriptor);
		return (0);
	}
	fclose(descriptor);
	sprintf(c_dir, "%s/%s", folder, PUB_FILENAME);
	descriptor = fopen(c_dir, "w");
	if (!descriptor)
	{
		return (0);
	}
	if (!PEM_write_EC_PUBKEY(descriptor, key))
	{
		fclose(descriptor);

		return (0);
	}
	fclose(descriptor);

	return (1);
}
