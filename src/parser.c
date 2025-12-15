#include "../inc/ft_ssl.h"

bool	get_algorithm(char *runner, uint8_t *options)
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
	else
		return (1);
	return (0);
}

bool	set_option(char runner, uint8_t *options)
{
	switch(runner)
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
		default:
			fprintf(stderr, "ft_ssl: Invalid option '%c'. Run './ft_ssl -h' to print usage.\n", runner);
			return (1);
	}
	return (0);
}

bool	parser(char **argv, uint8_t *options, char ***inputs)
{
	char	**runner = argv + 1; // skip program's name
	bool	no_algo	= 0;
	
	no_algo = get_algorithm(*runner, options);
	if (!no_algo)
		++runner;
	while (*runner != NULL && **runner == '-' && !(*options & STRING))
	{
		if (set_option(*(*runner + 1), options) == 1)
			return (1);
		++runner;
	}
	if ((*options & USAGE) == 0 && no_algo)
	{
		fprintf(stderr, "ft_ssl: invalid algorithm. Run \"./ft_ssl -h\" for usage\n");
		return (1);
	}
	else if ((*options & STRING) != 0 && *runner == NULL)
	{
		write(STDERR_FILENO, "ft_ssl: '-s' options gets a invalid argument. Run './ft_ssl -h' for usage.\n", 75);
		return (1);
	}
	*inputs = runner;
	return (0);
}