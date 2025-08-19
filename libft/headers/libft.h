/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:05:45 by zslowian          #+#    #+#             */
/*   Updated: 2025/04/10 21:21:41 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define BUF_SIZE 4096
# define FLAGS "+ 0-#"
# define NUMBERS "0123456789"
# define SPECIFIERS "cspdiuxX%"
# define PADDING_SPACE " "
# define LOW_SYMBOLS "0123456789abcdef"
# define UP_SYMBOLS "0123456789ABCDEF"

# include <limits.h> // INT_MAX, INT_MIN
# include <stdarg.h> // variadic macros
# include <stdbool.h> // bool
# include <stdio.h> // TODO: replace with ft_printf once all test pass correctly
# include <stdlib.h> // malloc free
# include <unistd.h> // write

/**
 * List structure for linked list implementation
 *
*/
typedef struct s_list
{
	void			*content;
	int				lst_size;
	struct s_list	*next;
}	t_list;

/**
 * Enum structure to choose the base conversion of a number
 * to print
 *
 */
typedef enum e_base
{
	BASE_2 = 2,
	BASE_8 = 8,
	BASE_10 = 10,
	BASE_16 = 16,
}	t_base;

/**
 * Enum structure to hold possible errors that can be thrown
 * in libft library
 *
*/
typedef enum e_libft_error
{
	OK = 0,
	MALLOC_ERROR = -67,
	PARSE_ERROR = -87,
}	t_libft_error;

/**
 * Shorthand for the unsigned char type
 *
 */
typedef unsigned char	t_byte;

/**
 * Union structure to hold the value of a number to print
 * regardless of conversion
 *
 */
typedef union u_value
{
	long			l_value;
	unsigned long	ul_value;
}	t_value;

/**
 * Structure to hold all the possible formatting flags
 * passed to the ft_printf function in the format string
 *
 */
typedef struct s_format
{
	/**
	 * left-adjusted
	 */
	bool	minus;
	/**
	 * number sign (+ or -) before the number for signed conversion
	 */
	bool	plus;
	/**
	 * blank should be left before a positive number (or empty string)
	 * produced by a signed conversion
	 */
	bool	space;
	/**
	 * The value should be converted to an "alternative form"
	*/
	bool	hash;
	/**
	 * The value should be zero padded
	*/
	bool	zero_pad;
	/**
	 * Precision flag to know if we should look at the precision value or not
	*/
	bool	is_precision;
	// cspdiuxX% format specifiers
	char	specifier;
	t_base	base;
	bool	upper_case;
	// width and precision values
	int		width;
	int		precision;
	int		nbr_padding_spaces;
	int		nbr_padding_zeros;
	bool	is_number_negative;
	bool	is_number_negated;
	bool	nil;
	// lenght of the number string to be printed out
	int		nbr_length;
}	t_format;

/**
 * Structure holding all the necessary data used in this library
 * to print the string correctly
 *
 */
typedef struct s_data
{
	// Format string - first argument to the printf function
	const char	*str;
	// ft_printf library structure holding all the formatting flags
	t_format	format;
	// My variable list of arguments
	va_list		arg_ptr;
	// Number of chars output in the end (returned from ft_printf)
	int			nbr_chars;
	// Pointer to my 4K memory buffer
	char		*buffer;
	// Index of the next empty int slot in tbe memory buffer
	int			buffer_index;
	// Temporary buffer for handling number printing
	char		temp[64];
	// Value to print in the on chosen fd
	t_value		value_to_print;
}	t_data;

// IS functions
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

// LIST functions
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// MEMORY functions
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *string, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// MATH functions
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_absolute(int nb);

// PUT/PRINT functions
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

// TO functions
char	*ft_itoa(int n);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
double	ft_atodbl(char *s);

// STRING functions
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strreplace(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_clear_char_array(char ***arr, int arr_size);
void	ft_print_char_array(char **arr, int arr_size);
int		ft_strnchar(char *str, char c);

// FT_PRINTF functions
bool	ft_in(const char *str, char c);
int		ft_parsef(t_data *data);
int		ft_printf(const char *str, ...);
void	my_memset(void *ptr, t_byte value, size_t n);
void	ft_set_padding_zeros(t_data *data);
void	ft_negate_number(t_data *data, t_value int_value);
void	ft_write_buffer(t_data *data, char c);
void	ft_flush_buffer(t_data *data);
void	ft_putchar_buffer(char c, int precision, t_data *data);
void	ft_putstring_buffer(char *str, size_t precision, t_data *data);
void	ft_render_char(t_data *data, int c);
void	ft_render_string(t_data *data, char *str);
void	ft_render_number(t_data *data);
void	ft_itoa_buffer(t_data *data, t_value int_value);

void	print_my_structure(char *ft_name, t_data *data);
void	print_width_precision(char *ft_name, t_data *data);

// GNL functions
char	*get_next_line(int fd);
char	*ft_read_to_buffer(char *buffer, int fd, char end);

#endif
