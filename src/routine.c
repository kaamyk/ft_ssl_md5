#include "../inc/ft_ssl.h"

void	MDString(const uint8_t options, const char *name, const char *to_hash)
{
	uint8_t		digest[MD5_HSSZ] = {0};
	t_MD5_CTX	context = {0};
	
	MD5Init(&context);
	MD5Update(&context, (uint8_t *)to_hash, strlen(to_hash));
	MD5Final(digest, &context);
	display(digest, options, name, to_hash);
}

void	SHAString(const uint8_t options, const char *name, const char *to_hash)
{
	(void) options;
	(void) name;
	t_SHA256_CTX	context = {0};
	uint8_t	digest[32] = {0};
	
	if (SHA256Reset(&context))
		printf("Reset err\n");
	else if (SHA256Input(&context, (const uint8_t *)to_hash, strlen(to_hash)))
		printf("Input err\n");
	else if (SHA256Result(&context, (uint8_t *)digest))
		printf("Result err\n");
	display(digest, options, name, to_hash);
}

void	launch_algo(uint8_t options, char *name, char* to_hash)
{
	if (options & MD5)
		MDString(options, name, to_hash);
	else if (options & SHA256)
		SHAString(options, name, to_hash);
}

void	routine(t_data data)
{
	char	*file_content = NULL;
	
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
	while (*data.inputs != NULL)
	{
		file_content = file_to_str(*data.inputs);
		if (file_content != NULL)
			launch_algo(data.options, *data.inputs, file_content);
		free(file_content);
		data.inputs++;
	}
}