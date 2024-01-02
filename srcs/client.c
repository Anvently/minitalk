/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:23:12 by npirard           #+#    #+#             */
/*   Updated: 2024/01/02 16:04:31 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/02 14:22:00 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <minitalk.h>
#include <string.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>

/* static void	catch_signal(int signo)
{
	printf("SIGNAL CATCHED : %d\n", signo);
} */

void	ft_send_char(int pid, char c)
{
	int				i;
	unsigned char signal;

	i = 8;
	while (i--)
	{
		signal = c >> i & 1;
		printf("%d", signal);
		if (!signal)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		kill(pid, signal);
		usleep(100);
	}
	printf("\n");
}

void	ft_send_str(int pid, char *str)
{
	printf("String to send (%d):\n%s\n", pid, str);
	while (*str)
		ft_send_char(pid, *str++);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (error(0, "unsufficient number of parameters"));
	if (ft_strtoi(argv[1], &pid))
		return (error(0, "incorrect pid"));
	ft_send_str(pid, argv[2]);
	return (0);
}

/*
int	main(void)
{
	int		fd;
	char	*line;
	char	*path;

	while ((path = readline("")))
		free(path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error(errno, path);
	while ((line = ft_gnl(fd)))
		ft_putstr_fd(line, 1);
	free(line);
	free(path);
	return (0);
} */
