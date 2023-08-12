/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:38:25 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/12 20:13:38 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_ph {
	int	n_philo;
}	t_ph;

/*
** Main
*/

void	exit_error(char *e);
t_ph	*ft_ph(void);

/*
** Analyzer
*/

void	ft_analyzer(char **vargs);

/*
** Utils
*/

int		ft_perror(char *e, int n);
void	ft_putendl_fd(char *s, int fd);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_isint(char *nb);
int		ft_strcmp(char *s1, char *s2);

#endif
