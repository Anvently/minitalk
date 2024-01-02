/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:37:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/02 16:04:11 by npirard          ###   ########.fr       */
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
#include <strings.h>

t_data	data;

static void	catch_signal(int signo)
{
	data.count++;
	if (signo == SIGUSR1)
		data.c = (data.c << 1) | 0;
	else if (signo == SIGUSR2)
		data.c = (data.c << 1) | 1;
	if (data.count == 8)
	{
		ft_putchar_fd(data.c, 1);
		data.count = 0;
		data.c = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	bzero(&act, sizeof(struct sigaction));
	act.sa_handler = catch_signal;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	printf("SERVER PID : %d\n", getpid());
	while (1)
		continue ;
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
