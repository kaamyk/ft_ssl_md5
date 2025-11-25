#include "../inc/ft_ssl_md5.h"
#include <stdint.h>
#include <stdio.h>

void	decode(uint32_t *output, uint8_t *input, uint32_t len)
{
	for (uint32_t i = 0, j = 0; j < len; i++, j += 4)
	{
		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) | (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
	}
}

void	encode(uint8_t *output, uint32_t *input, uint32_t len)
{
	for (uint32_t i = 0, j = 0; j < len; i++, j += 4)
	{
		output[j] = (uint8_t)(input[i] & 0xff);
		output[j + 1] = (uint8_t)((input[i] >> 8) & 0xff);
		output[j + 2] = (uint8_t)((input[i] >> 16) & 0xff);
		output[j + 3] = (uint8_t)((input[i] >> 24) & 0xff);
	}
}

uint8_t	*MD5memcpy(uint8_t *dest, const uint8_t *src, const uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

void	MD5memset(uint8_t *output, const uint8_t value, const uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		output[i] = value;
	}
}

char	*file_to_str(char *filename)
{
	char	*content = NULL;
	char	*buf[256] = {0};
	char	*tmp = NULL;
	FILE	*file = fopen(filename, "r");
	
	if (file == NULL)
	{
		fprintf(stderr, "ft_ssl: fopen: '%s': %s\n", filename, strerror(errno));
		return (NULL);
	}
	while (fgets((char *)buf, 255, file))
	{
		tmp = content;
		if (content != NULL)
			content = ft_strjoin(content, (char *)buf);
		else
			content = strdup((char *)buf);
		if (content == NULL)
		{
			fprintf(stderr, "ft_ssl: fatal error: %s\n", strerror(errno));
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	if (ferror(file))
		fprintf(stderr, "ft_ssl: fgets: %s\n", strerror(errno));
	fclose(file);
	return (content);
}