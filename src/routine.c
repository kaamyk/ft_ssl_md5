#include "../inc/ft_ssl.h"

void	launch_algo(const t_data *data, char *to_hash)
{
	switch (data-> options & 0x1C00)
	{
		case MD5:
			MDString(data, to_hash);
			break ;
		case SHA256:
			SHAString(data, to_hash);
			break ;
		case BASE64:
			B64String(data, to_hash);
			break ;
	}
}

void	inputs_loop(t_data *data)
{
	char	*file_content = NULL;
	
	while (*data->inputs)
	{
		if (!(data->options & BASE64) || data->options & IN_FILE)
			file_content = file_to_str(*data->inputs);
		if (file_content != NULL)
		{
			launch_algo(data, file_content);
			free(file_content);
		}
		data->inputs++;
	}
}

void	routine(t_data *data)
{
	if (data->options & USAGE)
	{
		if (write(STDOUT_FILENO, "ft_ssl usage:\n\techo string | ./ft_ssl algorithm [options] [-s \"string\"] arguments\nalgorithm values : selects the hash algorithm to run\n\tsha256\n\tmd5\noptions: \n\tsets the display format :\n\t\t-p : print stdin to stdout and append the checksum to stdout.\n\t\t-q : quiet mode\n\t\t-r : reverse the format of the ouput\n\t-s : print the sum of the given string. Any argument after this option is consider as a string. Each argument after the string is consider as a filename (see arguments section).\n\t-h : print usage\narguments :\n\t Each is considered has a file name. The command tries to open each file, is it fails it goes on.\n", 615) == -1)
			return ;
		return ;
	}
	if (data->options & IS_PIPE)
	{
		printf("Dans PIPE\n");
		launch_algo(data, data->pipe);
		data->options &= ~(IS_PIPE);
	}
	if (data->options & STRING)
	{
		launch_algo(data, *(data->inputs++));
		data->options &= ~(STRING);
	}
	if (data->options & IN_FILE)
	{
		printf("Dans INFILE\n");
		launch_algo(data, data->in_file);
	}
	if (data->inputs)
		inputs_loop(data);
}