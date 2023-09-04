/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:38:25 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/01 20:25:01 by echavez-         ###   ########.fr       */
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

struct				s_id;

typedef struct s_ph {
	int				n_philo;
	int				die;
	int				eat;
	int				sleep;
	int				times_eat;
	int				*stomach_full;
	struct s_id		*ids;
	pthread_mutex_t	*forks;
	pthread_t		*philo;
	pthread_t		lamuerte;
	pthread_mutex_t	data_meal;
	pthread_mutex_t	data_stomach;
}	t_ph;

typedef struct s_id {
	int						id;
	t_ph					*ph;
	unsigned long long		time_last_meal;
	int						meal_counter;

}	t_id;

/*
** Main
*/

void				exit_error(char *e, t_ph *ph);
void				ft_destructor(t_ph *ph);

/*
** Analyzer
*/

t_ph				*ft_arg_parser(char **vargs);
t_ph				*ft_ph(void);

/*
** Actions
*/

void				takes_forks(t_ph *ph, t_id *id, int lfork, int rfork);
void				ph_eats(t_ph *ph, t_id *id, int lfork, int rfork);
void				ph_sleeps(t_ph *ph, t_id *id);

/*
** Philosopher
*/

t_ph				*create_philosophers(t_ph *ph);
void				check_if_dead(t_ph *ph, t_id *id, 
						unsigned long long time_last_meal);
unsigned long long	get_timestamp_in_ms(void);

/*
** Muerte
*/

void				*lamuerte(void *arg);

/*
** Fork
*/

t_ph				*create_forks(t_ph *ph);
t_ph				*destroy_forks(t_ph *ph);

/*
** Utils
*/

int					ft_perror(char *e, int n);
void				ft_putendl_fd(char *s, int fd);
int					ft_putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *str);
void				ft_putchar_fd(char c, int fd);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
int					ft_isint(char *nb);
int					ft_strcmp(char *s1, char *s2);

#endif
