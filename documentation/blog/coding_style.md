[Back to Home page](../../README.md)

coding style
============

### WORK IN PROGRESS ###

Here is the the source code of ```f_printf``` function for _FAT File System_ implementation (version R0.12c) done by
_ELM ChaN_.

```c
/*-----------------------------------------------------------------------*/
/* Put a formatted string to the file                                    */
/*-----------------------------------------------------------------------*/

int f_printf (
	FIL* fp,			/* Pointer to the file object */
	const TCHAR* fmt,	/* Pointer to the format string */
	...					/* Optional arguments... */
)
{
	va_list arp;
	putbuff pb;
	BYTE f, r;
	UINT i, j, w;
	DWORD v;
	TCHAR c, d, str[32], *p;


	putc_init(&pb, fp);

	va_start(arp, fmt);

	for (;;) {
		c = *fmt++;
		if (c == 0) break;			/* End of string */
		if (c != '%') {				/* Non escape character */
			putc_bfd(&pb, c);
			continue;
		}
		w = f = 0;
		c = *fmt++;
		if (c == '0') {				/* Flag: '0' padding */
			f = 1; c = *fmt++;
		} else {
			if (c == '-') {			/* Flag: left justified */
				f = 2; c = *fmt++;
			}
		}
		while (IsDigit(c)) {		/* Precision */
			w = w * 10 + c - '0';
			c = *fmt++;
		}
		if (c == 'l' || c == 'L') {	/* Prefix: Size is long int */
			f |= 4; c = *fmt++;
		}
		if (!c) break;
		d = c;
		if (IsLower(d)) d -= 0x20;
		switch (d) {				/* Type is... */
		case 'S' :					/* String */
			p = va_arg(arp, TCHAR*);
			for (j = 0; p[j]; j++) ;
			if (!(f & 2)) {
				while (j++ < w) putc_bfd(&pb, ' ');
			}
			while (*p) putc_bfd(&pb, *p++);
			while (j++ < w) putc_bfd(&pb, ' ');
			continue;

		case 'C' :					/* Character */
			putc_bfd(&pb, (TCHAR)va_arg(arp, int)); continue;

		case 'B' :					/* Binary */
			r = 2; break;

		case 'O' :					/* Octal */
			r = 8; break;

		case 'D' :					/* Signed decimal */
		case 'U' :					/* Unsigned decimal */
			r = 10; break;

		case 'X' :					/* Hexdecimal */
			r = 16; break;

		default:					/* Unknown type (pass-through) */
			putc_bfd(&pb, c); continue;
		}

		/* Get an argument and put it in numeral */
		v = (f & 4) ? (DWORD)va_arg(arp, long) : ((d == 'D') ? (DWORD)(long)va_arg(arp, int) : (DWORD)va_arg(arp, unsigned int));
		if (d == 'D' && (v & 0x80000000)) {
			v = 0 - v;
			f |= 8;
		}
		i = 0;
		do {
			d = (TCHAR)(v % r); v /= r;
			if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
			str[i++] = d + '0';
		} while (v && i < sizeof str / sizeof str[0]);
		if (f & 8) str[i++] = '-';
		j = i; d = (f & 1) ? '0' : ' ';
		while (!(f & 2) && j++ < w) putc_bfd(&pb, d);
		do {
			putc_bfd(&pb, str[--i]);
		} while (i);
		while (j++ < w) putc_bfd(&pb, d);
	}

	va_end(arp);

	return putc_flush(&pb);
}
```

I'll be using some bits of it here to describe things that really annoy me when reading code and trying to understand
it.

What I think of it, basically, is that it is not understandable by anybody who hasn't bee involved in the project from
the begining (at least for a very long time).


Indentation
-----------
* Space characters are used instead of tabulation
* One indentation is 4 space


Global stament indication
-------------------------

* One statement per line. **No exception.**
```c
while (*p) putc_bfd(&pb, *p++);
```
Previous line is basically **3** statements on the same line :
  - ```while``` statement with a condition on the value pointed by ```p```
  - a call to ```putc_bfd``` function
  - incrementation of the value pointed by ```p``` (or is it the address... quite confusing isn't it ?)
  
If there is any problem (lets say ```p``` is incremented one time too many) with any one of these 3 statements,
debugging will turn into an absolute nightmare : how can we figure out easily how we have manipulated a value that
has absolutely no sense ? Is it because of ```*p++``` incrementation ? is it a bug in ```putc_bfd``` ? <br>
=> No obvious answer

* There should be a blank line after each conditional or loop statement

```c
/*
 * --------------------------------------------------------
 * if statement example
 * --------------------------------------------------------
 */
if( a_condition )
{
	// conditional statement code
}

// some unconditional code

/*
 * --------------------------------------------------------
 * for statement example
 * --------------------------------------------------------
 */
for( int foo = 0 ; foo < bar ; foo++ )
{
	// in loop code
}

// some code outside of the loop
```


IF statement
------------

* ```if``` statement style must follow the style :
  - No space between ```if``` keyword and opening parenthesis.
  - One space after opening parenthesis and one space before closing parenthesis.
  - Opening bracket is on the next line, alone, on the same column as ```if``` keyword
  - Conditional code is at the next line, indented one time.
  - Closing bracket is alone, on the same column as ```if``` keyword, on a new line
* There should be no value affectation when evaluating a condition.

```c
if( a = memcmp( foo, bar, sizeof(foo) ) )
```

Previous example is absolutely forbidden.

* Condition evauation must be explicit, even in case of boolean. **No exception.**

```c
if( boolean_condition )			// this is wrong
if( true == boolean_condition )	// this is right

if( integer_condition )			// this is wrong
if( integer_condition > 0 )		// this is right
```

* It is preferable to write conditions the way ```if( CONSTANT_VALUE == a_condition )``` instead of the usual
```if( a_condition == CONSTANT_VALUE )```. If a ```=``` character has been forgotten, the compiler will complain about
it (cannot affect value to a constant value).

* If there is kind of operation that are involved in a condition, it should be surrounded by parenthesis to avoid
evaluating the expressions with an unexpected priority.

```c
if( idx & ~0xC0FFEEUL != idx )
```

In previous example, we suppose that the precedence is to do `idx & ~0xC0FFEEUL` and then compare the result to `idx`.
But that depends on the compiler. Precedence could be as well to evaluate `~0xC0FFEEUL != idx` before doing the binary
`&` operation between the result and `idx`.


INLINE IF operations
--------------------

_Inline if_ opérationas are forbidden. **No Exception.**

```c
v = (f & 4) ? (DWORD)va_arg(arp, long) : ((d == 'D') ? (DWORD)(long)va_arg(arp, int) : (DWORD)va_arg(arp, unsigned int));
```
_This is an absolute joke_ ! (not a funny one)

It is not readable nor understandable at all when reading it for the first time. It takes me minutes to figure out
what is happening here. I cannot afford to spend 5 to 10 minutes wondering about the meaning of every line of code a
colleague wrote when I am reviewing it or if I have to maintain it for some reason.


MACRO
-----

* Macro should never be used where a function can do the same thing
* Macro should never redefine a C language keyword

```c
#define if    while // funny stuff like this should never be seen
```


Inline functions
----------------

Using _inline functions_ should only happen where performance and timings are critical for the system.


GOTO statement
--------------

```goto``` statements are forbidden. **No exception.**


RETURN statement
----------------

A return statement should never be hidden into a Macro

```c
#define DEVICE_CHECK( device, index ) 						\
	do 														\
	{														\
		if( device == NULL ) 								\
		{													\
			printf( "No such device (index=%d)\n", index );	\
			return;											\
		}													\
	} while( 0 )
	
void create_device_counter( void *p_device ) 
{
	int retcode = ERROR_NONE;
	unsigned int counter_nb = 0xFFUL;	//< Default value : No counter
	DeviceCounter_t device_cnt = *p_device;
	
	CHECK_DEVICE( device, DEV_ALLOW_INDEX );

	retcode = set_device_counter( device_cnt, &counter_nb );

	if( retcode == ERROR_NONE )
	{
		printf( "Counter no. 0x%02x is set for device %s\n", counter_nb, device_cnt.name );
	}

	printf( "Exit status is %d\n" , retcode );
}
```

For this example, I have put both macro definition and the function that uses it close oe to the other. But, what if
the macro is defined in some obscure ```<utils.h>``` header file. Furthermore, what if it is defined in a compiled
library ? 

It fucks up your mind if you read the code and can't see explicitly all exit points of a function.

**Note :** In code sample above, using `do{ /* some code */} while( 0 )` inside of the macro forces to add `;` when using it.


Comments
--------

* One line comments must use `// ... ` style. It is defined since _C99_, that's long enough for it to be standard.
* Multi-line comment must follow the style :

```c
/*
 * Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus.
 * Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor.
 */
```

* _Doxygen_ or any other documentational comments should use `//! ... ` for one line comments and

```
/**
  * @brief Cras elementum ultrices diam.
  * @details Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, 
  *          orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat.
  */
```

for multi line comments.


[Back to Home page](../../README.md)
