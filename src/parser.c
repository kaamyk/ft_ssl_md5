#include "../inc/ft_ssl.h"

bool	get_algorithm(char *runner, uint16_t *options)
{
	if (runner == NULL)
	{
		fprintf(stderr, "ft_ssl: no agorithm. Run \"./ft_ssl -h\" for usage\n");
		return (1);
	}
	else if (*runner == 'm' && !strcmp(runner, "md5"))
		*options |= MD5;
	else if (*runner == 's' && !strcmp(runner, "sha256"))
		*options |= SHA256;
	else if (*runner == 'b' && !strcmp(runner, "base64"))
		*options |= BASE64;
	else
		return (1);
	return (0);
}

bool	set_option(char runner, uint16_t *options)
{
	switch (runner)
	{
		case 'p':	// print input
			*options |= PRINT;
			break ;
		case 'q':	// quiet
			*options |= QUIET;
			break ;
		case 'r':	// reverse format
			*options |= REVERSE;
			break ;
		case 's':	// string
			*options |= STRING;
			break ;
		case 'h':	// help
			*options |= USAGE;
			break ;
		case 'e': 
			*options |= ENCODE;
			break ;
		case 'd': 
			*options |= DECODE;
			break ;
		case 'i': 
			*options |= IN_FILE;
			break ;
		case 'o': 
			*options |= OUT_FILE;
			break ;
		default:
			fprintf(stderr, "ft_ssl: Invalid option '%c'. Run './ft_ssl -h' to print usage.\n", runner);
			return (1);
	}
	return (0);
}

bool	parse_md5_sha256()
{
	return (0);
}

bool	parse_base64(char **runner, t_data *data)
{
	bool	error = 0;
	
	while (!error && *runner && **runner == '-')
	{
		if (set_option(*(*runner + 1), &data->options) == 1)
			return (1);
		if (!data->inputs && (data->options & IN_FILE))
		{
			if (++(*runner))
			{
				data->inputs = calloc(sizeof(char *), 2);
				*data->inputs = strdup(*runner);
			}
			else
				error = 1;
		}
		else if (data->options & OUT_FILE)
		{
			if (++runner)
			{
				printf("*runner == %s\n", *runner);
				data->out_file = strdup(*runner);
			}
			else
				error = 1;
		}
		++runner;
	}
	if (error)
	{
		fprintf(stderr, "ft_ssl: base64: missing arguments. Run \'./ft_ssl -h\' for usage.\n");
		return (1);
	}
	return (0);
}

bool	parser(char **argv, t_data *data)
{
	char	**runner = argv + 1; // skip program's name
	bool	no_algo	= 0;
	
	no_algo = get_algorithm(*runner, &data->options);
	if (!no_algo)
		++runner;
	if (data->options & BASE64)
		parse_base64(runner, data);
	else if (data->options & MD5 || data->options & SHA256)
	{
		while (*runner && **runner == '-' && !(data->options & STRING))
		{
			if (set_option(*(*runner + 1), &data->options) == 1)
				return (1);
			++runner;
		}
		if (!(data->options & USAGE) && no_algo)
		{
			fprintf(stderr, "ft_ssl: invalid algorithm. Run \"./ft_ssl -h\" for usage\n");
			return (1);
		}
		else if ((data->options & STRING) != 0 && *runner == NULL)
		{
			write(STDERR_FILENO, "ft_ssl: '-s' options gets a invalid argument. Run './ft_ssl -h' for usage.\n", 75);
			return (1);
		}
		data->inputs = runner;
	}
	return (0);
}