#include "../inc/ft_ssl_md5.h"

bool	parser(int argc, char **argv, uint8_t *options)
{
	(void) argc;
	(void) argv;
	(void) options;
	char	**runner = argv + 1; // skip program's name
	
	while (*runner != NULL)
	{
		if (**runner == '-')
		{
			switch(*++(*runner))
			{
				case 'p':	// print input
					break ;
				case 'q':	// quiet
					break ;
				case 'r':	// reverse format
					break ;
				case 's':	// string
					break ;
				default:
					fprintf(stderr, "ft_ssl: Invalid option '%c'. Try 'ft_ssl -h' to print usage.\n", **runner);
					return(1);
			}
		}
	}
	return (0);
}