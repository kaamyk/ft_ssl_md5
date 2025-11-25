#include "../inc/ft_ssl_md5.h"

void	header_display(uint8_t options, const char *name, const char *to_hash)
{
	if (options & IS_PIPE)
	{
		if (options & PRINT)
			printf("(\"%s\")= ", to_hash);
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

void	MDPrint (const uint8_t digest[16])
{
	for (uint8_t i = 0; i < 16; i++)
	printf ("%02x", digest[i]);
}

void	MDdisplay(const uint8_t digest[16], uint8_t options, const char *name, const char *to_hash)
{
	if (!(options & QUIET))
		header_display(options, name, to_hash);
	MDPrint (digest);
	if (options & REVERSE)
	{
		if (name != NULL)
			printf(" %s", name);
		else
			printf(" \"%s\"", to_hash);
	}
	fflush(stdout);
	write (STDOUT_FILENO, "\n", 1);
}