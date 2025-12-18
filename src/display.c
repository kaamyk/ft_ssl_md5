#include "../inc/ft_ssl.h"

void	header_display(FILE *stream , uint16_t options, const char *name, const char *to_hash)
{
	size_t	to_print_size = strlen(to_hash);

	if (options & IS_PIPE)
	{
		if (to_hash[to_print_size - 1] == '\n')
			--to_print_size;
		if (options & PRINT)
			fprintf(stream, "(\"%s\")= ", to_hash);
		else
			fprintf(stream, "(stdin)= ");
	}
	else if (!(options & REVERSE))
	{
		fprintf(stream, "MD5 ");
		if (options & STRING)
			fprintf(stream, "(\"%s\")= ", to_hash);
		else
			fprintf(stream, "(%s)= ", name);
	}
}

uint8_t	define_digest_size(uint16_t options)
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

void	hash_display(FILE *stream, const uint8_t digest[16], uint16_t options, const char *infilename, const char *to_hash)
{
	uint8_t	digest_size = define_digest_size(options);
	
	if (!(options & QUIET))
		header_display(stream, options, infilename, to_hash);
	for (uint8_t i = 0; i < digest_size; i++)
		fprintf (stream,"%02x", digest[i]);
	if ((options & REVERSE) && !(options & IS_PIPE))
	{
		if (infilename)
			fprintf(stream, " %s", infilename);
		else
			fprintf(stream, " \"%s\"", to_hash);
	}
	fprintf(stderr, "\n");
}

void	display(const uint8_t *digest, const t_data *data, const char *infilename, const char *to_hash)
{
	printf("display(outfile = [%s])\n", data->out_file);
	FILE	*stream = stdout;

	if (data->options & OUT_FILE && data->out_file)
	{
		stream = fopen(data->out_file, "a");
		if (stream == NULL)
		{
			fprintf(stderr, "ft_ssl: display: %s\n", strerror(errno));
			return ;
		}
	}
	if (data->options & (SHA256 | MD5))
		hash_display(stream, digest, data->options, infilename, to_hash);
	else if (data->options & BASE64)
		fprintf(stream, "%s\n", digest);
	if (stream != stdout)
		fclose(stream);
}
