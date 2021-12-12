CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3 -c
TMPDIR = trash/

FILES = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c ec_save.c ec_load.c ec_sign.c ec_verify.c
O_FILES = $(addprefix $(TMPDIR), $(FILES:%.c=%.o))

libhblk_crypto.a: hblk_crypto.h $(TMPDIR) $(O_FILES)
	ar rcs libhblk_crypto.a $(O_FILES)

$(TMPDIR)%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(TMPDIR):
	mkdir $(TMPDIR)
