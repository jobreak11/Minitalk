/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeepach <gyeepach@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:23:56 by gyeepach          #+#    #+#             */
/*   Updated: 2024/07/22 09:10:22 by gyeepach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minitalk.h"

static void	ft_send_next_char_to_bit(unsigned char c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(500);
	}
}

static void	ft_send_len_to_bit(int len, int pid)
{
	int i;

	i = -1;
	while (++i < 32)
	{
		if (len & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		usleep(500);
	}
}

static int	is_not_pid_number(char *args, int argc)
{
	int number;

	number = 0;

	if (argc != 3)
		return (1);
	while (args[number] == ' ' || args[number] == '\t')
		number++;
	if (args[number] == '-')
		return (1);
	while (args[number])
	{
		if (args[number] >= '0' && args[number] <= '9')
			number++;
		else
			return (1);
	}
	return (0);
}


int main(int argc, char *argv[])
{
	// struct sigaction	action;
	int					len;
	int					i;
	int					access_server_pid;
	char				*msg_to_server;

	if (is_not_pid_number(argv[1], argc))
		return (-1);
	if (argc == 3)
	{
		access_server_pid = ft_atoi(argv[1]);
		msg_to_server = argv[2];
		len = ft_strlen(msg_to_server);
		i = -1;
		// action.sa_sigaction = handler;
		// sigemptyset(&action.sa_mask);
		// action.sa_flags = SA_SIGINFO;
		// sigaction(SIGUSR1, &action, NULL);
		// sigaction(SIGUSR2, &action, NULL);
		ft_send_len_to_bit(len, access_server_pid);
		while (msg_to_server[++i])
			ft_send_len_to_bit(msg_to_server[i], access_server_pid);
		ft_send_next_char_to_bit(msg_to_server[i], access_server_pid);
	}
}