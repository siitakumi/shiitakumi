/* getch�^putch�p�w�b�_		"getputch.h" */

#if !defined(__GETPUTCH)

  #define __GETPUTCH

  #if defined(_MSC_VER) || (__TURBOC__) || (LSI_C)

	/* MS-Windows�^MS-DOS�iVisual C++, Borland C++, LSI-C 86 etc ...�j */

	#include <conio.h>

	static void init_getputch(void) { /* �� */ }

	static void term_getputch(void) { /* �� */ }


  #else

	/* Curses���C�u�������񋟂����UNIX�^Linux�^OS X */

	#include <curses.h>

	#undef putchar
	#undef puts
	#undef printf
	static char __buf[4096];

	/*--- __putchar�Fputchar�֐��Ɠ����i���s��[���s�{���A]�ŏo�́j---*/
	static int __putchar(int ch)
	{
		if (ch == '\n')
			putchar('\r');
		return (putchar(ch));
	}

	/*--- putch�F�P�����\�����ăo�b�t�@��|���o�� ---*/
	static int putch(int ch)
	{
		int result = putchar(ch);

		fflush(stdout);
		return (result);
	}

	/*--- __printf�Fprintf�֐��Ɠ����i���s��[���s�{���A]�ŏo�́j---*/
	static int __printf(const char *format, ...)
	{
		va_list	ap;
		int 	count;

		va_start(ap, format);
		vsprintf(__buf, format, ap);
		va_end(ap);

		for (count = 0; __buf[count]; count++) {
			putchar(__buf[count]);
			if (__buf[count] == '\n')
				putchar('\r');
		}
		return (count);
	}

	/*--- __puts�Fputs�֐��Ɠ����i���s��[���s�{���A]�ŏo�́j---*/
	int __puts(const char *s)
	{
		int i, j;

		for (i = 0, j = 0; s[i]; i++) {
			__buf[j++] = s[i];
			if (s[i] == '\n')
				__buf[j++] = '\r';
		}
		return (puts(__buf));
	}

	/*--- ���C�u������������ ---*/
	static void init_getputch(void)
	{
		initscr();
		cbreak();
		noecho();
		refresh();
	}

	/*--- ���C�u�����I������ ---*/
	static void term_getputch(void)
	{
		endwin();
	}

	#define putchar	__putchar
	#define	printf	__printf
	#define puts	__puts

  #endif

#endif
