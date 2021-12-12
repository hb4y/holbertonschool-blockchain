#include "hblk_crypto.h"

/**
 * ec_from_pub - EC struct
 * @pub: key
 * Return: EC_KEY
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *k_struct;
	const EC_GROUP *group;
	EC_POINT *point;

	if (pub == NULL)
		return (NULL);
	k_struct = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!k_struct)
		return (NULL);
	group = EC_KEY_get0_group(k_struct);
	point = EC_POINT_new(group);
	if (!point)
	{
		EC_KEY_free(k_struct);

		return (NULL);
	}
	if (!EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL)
		|| !EC_KEY_set_public_key(k_struct, point))
	{
		EC_KEY_free(k_struct);
		EC_POINT_free(point);

		return (NULL);
	}
	EC_POINT_free(point);


	return (k_struct);
}
