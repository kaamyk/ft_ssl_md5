#include "../inc/ft_ssl.h"

/* ERROR DISPLAY */
bool	parse_error(char *message, const char *algostr)
{
	fprintf(stderr, "ft_ssl: %s: %s. Run 'ft_ssl -h' for usage.\n", algostr, message);
	return (1);
}

/* NORMAL DISPLAY */
void	header_display(FILE *stream , const t_data *data, const char *to_hash)
{
	size_t	to_print_size = strlen(to_hash);

	if (data->options & IS_PIPE)
	{
		if (to_hash[to_print_size - 1] == '\n')
			--to_print_size;
		if (data->options & PRINT)
			fprintf(stream, "(\"%s\")= ", to_hash);
		else
			fprintf(stream, "(stdin)= ");
	}
	else if (!(data->options & REVERSE))
	{
		fprintf(stream, "%s ", data->algostr[(data->options & 0x1C00) >> 10]);
		if (data->options & STRING)
			fprintf(stream, "(\"%s\")= ", to_hash);
		else
			fprintf(stream, "(%s)= ", *data->inputs);
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

void	hash_display(FILE *stream, const uint8_t digest[16], const t_data *data, const char *to_hash)
{
	uint8_t	digest_size = define_digest_size(data->options);
	
	if (!(data->options & QUIET))
		header_display(stream, data, to_hash);
	for (uint8_t i = 0; i < digest_size; i++)
		fprintf (stream,"%02x", digest[i]);
	if ((data->options & REVERSE) && !(data->options & IS_PIPE))
	{
		if (*data->inputs)
			fprintf(stream, " %s", *data->inputs);
		else
			fprintf(stream, " \"%s\"", to_hash);
	}
	fprintf(stream, "\n");
}

void	display(const uint8_t *digest, const t_data *data, const char *to_hash)
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
		hash_display(stream, digest, data, to_hash);
	else if (data->options & BASE64)
		fprintf(stream, "%s\n", digest);
	if (stream != stdout)
		fclose(stream);
}
