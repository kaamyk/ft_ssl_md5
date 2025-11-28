#include "../inc/ft_ssl.h"

void	header_display(uint8_t options, const char *name, const char *to_hash)
{
	size_t	to_print_size = strlen(to_hash);

	if (options & IS_PIPE)
	{
		if (to_hash[to_print_size - 1] == '\n')
			--to_print_size;
		if (options & PRINT)
		{
			write(STDOUT_FILENO, "(\"", 2);
			write(STDOUT_FILENO, to_hash, to_print_size);
			write(STDOUT_FILENO, "\")= ", 4);
		}
		else
			write(STDOUT_FILENO, "(stdin)= ", 10);
	}
	else if (!(options & REVERSE))
	{
		write(STDOUT_FILENO, "MD5 ", 4);
		if (options & STRING)
			printf("(\"%s\")= ", to_hash);
		else
			printf("(%s)= ", name);
	}
}

uint8_t	define_digest_size(uint8_t options)
{
	uint8_t	size = 0;

	switch(options & (MD5 | SHA256))
	{
		case MD5:
			size = MD5_HSSZ;
			break ;
		case SHA256:
			size = SHA256_HSSZ;
			break ;
		default:
			break ;
	}
	return (size);
}

void	display(const uint8_t digest[16], uint8_t options, const char *name, const char *to_hash)
{
	uint8_t	digest_size = define_digest_size(options);

	if (!(options & QUIET))
		header_display(options, name, to_hash);
	for (uint8_t i = 0; i < digest_size; i++)
		printf ("%02x", digest[i]);
	if ((options & REVERSE) && !(options & IS_PIPE))
	{
		if (name != NULL)
			printf(" %s", name);
		else
			printf(" \"%s\"", to_hash);
	}
	fflush(stdout);
	write (STDOUT_FILENO, "\n", 1);
}
