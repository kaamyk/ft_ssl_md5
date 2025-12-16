#include "../inc/ft_ssl.h"

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

char 	*read_stdin( void )
{
	char		buf[256] = {0};
	char	*tmp = NULL;
	char	*input = calloc(1, 1);
	if (input == NULL)
	{
		fprintf(stderr, "Fatal Error: calloc: %s\n", strerror(errno));
		return (NULL);
	}
	
	while (fread(buf, 1, 255, stdin) > 0)
	{
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

bool	is_in_pipe( void )
{
	struct stat	st = {0};
	
	if (fstat(STDIN_FILENO, &st) == -1)
	{
		fprintf(stderr, "ft_ssl: is_in_pipe(): fstat(): %s\n", strerror(errno));
		return (0);
	}
	return (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode));
}

bool	setup(char **argv, t_data *data)
{
	if (parser(argv, &data->options, &data->inputs) == 1)
		return (1);
	if ((!*data->inputs || (data->options & PRINT)) && is_in_pipe())
	{
		data->options |= IS_PIPE;
		data->pipe = read_stdin();
		if (data->pipe == NULL)
			return (1);
	}
	if (data->options & QUIET)
		data->options &= ~(PRINT | REVERSE);
	return (0);
}

int		main( int argc, char **argv )
{
	t_data	data = {0};
	
	(void) argc;
	
	if (setup(argv, &data) == 1)
	{
		free(data.pipe);
		exit (1);
	}
	routine(data);
	free(data.pipe);
	return (0);
}