#include "../inc/ft_ssl_md5.h"

void	print_args(char **argv)
{
	for (uint8_t i = 0; argv[i] != NULL; i++)
	{
		printf("argv[%d] == %s\n", i, argv[i]);
	}
}

char 	*get_input(uint8_t *options)
{
	char		buf[256] = {0};
	char	*tmp = NULL;
	char	*input = calloc(1, 1);
	if (input == NULL)
	{
		fprintf(stderr, "Fatal Error: calloc: %s\n", strerror(errno));
		return (NULL);
	}
	
	while (read(STDIN_FILENO, buf, 255) > 0)
	{
		*options |= IS_PIPE;
		tmp = input;
		if ((input = ft_strjoin(input, buf)) == NULL)
		{
			fprintf(stderr, "Fatal Error: ft_strjoin(): %s\n", strerror(errno));
			return (NULL);
		}
		free(tmp);
	}
	return (input);
}

void	MDString(const uint8_t options, const char *name, const char *to_hash)
{
	uint8_t		digest[16] = {0};
	t_MD5_CTX	context = {0};
	
	MD5Init(&context);
	MD5Update(&context, (uint8_t *)to_hash, strlen(to_hash));
	MD5Final(digest, &context);
	MDdisplay(digest, options, name, to_hash);
}

void	launch_algo(t_data data)
{
	char	*file_content = NULL;
	
	if (data.options & USAGE)
	{
		write(STDOUT_FILENO, "ft_ssl usage:\n\techo string | ./ft_ssl algorithm [options] [-s \"string\"] arguments\nalgorithm values : selects the hash algorithm to run\n\tsha256\n\tmd5\noptions: \n\tsets the display format :\n\t\t-p : print stdin to stdout and append the checksum to stdout.\n\t\t-q : quiet mode\n\t\t-r : reverse the format of the ouput\n\t-s : print the sum of the given string. Any argument after this option is consider as a string. Each argument after the string is consider as a filename (see arguments section).\n\t-h : print usage\narguments :\n\t Each is considered has a file name. The command tries to open each file, is it fails it goes on.\n", 615);
		return ;
	}
	if (data.options & IS_PIPE)
	{
		MDString(data.options, NULL, data.pipe);
		data.options &= ~(IS_PIPE);
	}
	if (data.options & STRING)
	{
		MDString(data.options, NULL, *(data.inputs++));
		data.options &= ~(STRING);
	}
	while (*data.inputs != NULL)
	{
		file_content = file_to_str(*data.inputs);
		if (file_content != NULL)
		{
			if (data.options & MD5)
				MDString(data.options, *data.inputs, file_content);
			// else if (data.options & SHA256)
			// 	SHAString(data.options, *data.inputs, file_content);
		}
		free(file_content);
		data.inputs++;
	}
}

void	print_arguments(char **argv)
{
	printf("================\n");
	printf("**argv:\n");
	while (*argv != NULL)
	{
		printf("\t%s\n", *(argv++));
	}
	printf("================\n");
}

int		main( int argc, char **argv )
{
	t_data	data = {0};
	
	(void) argc;
	
	print_arguments(argv);
	if (parser(argv, &data.options, &data.inputs) == 1)
	{
		free(data.pipe);
		return (1);
	}
	data.pipe = get_input(&data.options);
	if (data.pipe == NULL)
		return (1);
	launch_algo(data);
	free(data.pipe);
	return (0);
}