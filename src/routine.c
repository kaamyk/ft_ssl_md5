#include "../inc/ft_ssl.h"

void	MDString(const uint16_t options, const char *name, const char *to_hash)
{
	uint8_t		digest[MD5_HSSZ] = {0};
	t_MD5_CTX	context = {0};
	
	MD5Init(&context);
	MD5Update(&context, (uint8_t *)to_hash, strlen(to_hash));
	MD5Final(digest, &context);
	display(digest, options, name, to_hash);
}


bool	SHAString(const uint16_t options, const char *name, const char *to_hash)
{
	t_SHA256_CTX	context = {0};
	uint8_t	digest[32] = {0};
	
	if (SHA256Reset(&context))
	{
		fprintf(stderr, "ft_ssl: sha256: Reset err\n");
		return (1);
	}
	else if (SHA256Input(&context, (const uint8_t *)to_hash, strlen(to_hash)))
	{
		fprintf(stderr, "ft_ssl: sha256: Input err\n");
		return (1);
	}
	else if (SHA256Result(&context, (uint8_t *)digest))
	{
		fprintf(stderr, "ft_ssl: sha256: Result err\n");
		return (1);
	}
	display(digest, options, name, to_hash);
	return (0);
}

void	launch_algo(uint16_t options, char *filename, char* to_hash)
{
	switch (options & 0x1C00)
	{
		case MD5:
			MDString(options, filename, to_hash);
			break ;
		case SHA256:
			SHAString(options, filename, to_hash);
			break ;
		case BASE64:
			B64String(options, filename, to_hash);
			break ;
	}
}

void	inputs_loop(t_data data)
{
	char	*filename = NULL;
	char	*file_content = NULL;
	
	while (*data.inputs)
	{
		if (!(data.options & BASE64) || data.options & IN_FILE)
			file_content = file_to_str(*data.inputs);
		if (data.options & BASE64)
			filename = data.out_file;
		else
			filename = *data.inputs;
		if (file_content != NULL)
		{
			launch_algo(data.options, filename, file_content);
			free(file_content);
		}
		data.inputs++;
	}
}

void	routine(t_data data)
{
	printf("data->out_file = [%s]\n", data.out_file);
	if (data.options & USAGE)
	{
		write(STDOUT_FILENO, "ft_ssl usage:\n\techo string | ./ft_ssl algorithm [options] [-s \"string\"] arguments\nalgorithm values : selects the hash algorithm to run\n\tsha256\n\tmd5\noptions: \n\tsets the display format :\n\t\t-p : print stdin to stdout and append the checksum to stdout.\n\t\t-q : quiet mode\n\t\t-r : reverse the format of the ouput\n\t-s : print the sum of the given string. Any argument after this option is consider as a string. Each argument after the string is consider as a filename (see arguments section).\n\t-h : print usage\narguments :\n\t Each is considered has a file name. The command tries to open each file, is it fails it goes on.\n", 615);
		return ;
	}
	if (data.options & IS_PIPE)
	{
		launch_algo(data.options, NULL, data.pipe);
		data.options &= ~(IS_PIPE);
	}
	if (data.options & STRING)
	{
		launch_algo(data.options, NULL, *(data.inputs++));
		data.options &= ~(STRING);
	}
	if (data.inputs)
		inputs_loop(data);
}