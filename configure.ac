dnl Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([ClanBomber], [2.2.0], [rsl@member.fsf.org])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([1.14.1 subdir-objects dist-xz -Wall -Werror])


AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([11])
AC_LANG([C++])
AC_C_BIGENDIAN
AC_PROG_RANLIB
AM_GNU_GETTEXT_VERSION([0.19])
AM_GNU_GETTEXT([external])
AM_PROG_CC_C_O
AM_PROG_AR

#
# Add a define in config.h for host
#

AC_CANONICAL_HOST
AC_DEFINE_UNQUOTED([HOST_SYSTEM], ["$host"], [Host system])

#
# Check for for pthreads
#

AX_PTHREAD(, AC_MSG_ERROR([*** pthreads is required]))

#
# Check for Boost 1.46, at least (filesystem v3)
#

AX_BOOST_BASE(
	[1.46],
	,
	AC_MSG_ERROR([*** Boost is required])
)
AX_BOOST_ASIO
AX_BOOST_FILESYSTEM
AX_BOOST_PROGRAM_OPTIONS

#
# Check for SDL 1.2.0
#

PKG_CHECK_MODULES(
	[SDL],
	[sdl >= 1.2.0],
	,
	AC_MSG_ERROR([*** SDL required])
)
AC_SUBST(SDL_CFLAGS)
AC_SUBST(SDL_LIBS)

#
# Check for SDL_image
#

PKG_CHECK_MODULES(
	[SDL_IMAGE],
	[SDL_image],
	,
	AC_MSG_ERROR([*** SDL_image required])
)
AC_SUBST(SDL_IMAGE_CFLAGS)
AC_SUBST(SDL_IMAGE_LIBS)

#
# Check for SDL_mixer
#

PKG_CHECK_MODULES(
	[SDL_MIXER],
	[SDL_mixer],
	,
	AC_MSG_ERROR([*** SDL_mixer required])
)
AC_SUBST(SDL_MIXER_CFLAGS)
AC_SUBST(SDL_MIXER_LIBS)

#
# Check for SDL_ttf
#

PKG_CHECK_MODULES(
	[SDL_TTF],
	[SDL_ttf],
	,
	AC_MSG_ERROR([*** SDL_ttf required])
)
AC_SUBST(SDL_TTF_CFLAGS)
AC_SUBST(SDL_TTF_LIBS)

#
# Check for SDL_gfx
#

PKG_CHECK_MODULES(
	[SDL_GFX],
	[SDL_gfx],
	,
	AC_MSG_ERROR([*** SDL_gfx required])
)
AC_SUBST(SDL_GFX_CFLAGS)
AC_SUBST(SDL_GFX_LIBS)

#
# Enable console
#

AC_ARG_ENABLE(
	[console],
	[AS_HELP_STRING([--enable-console], [enable console (default=no)])],
	,
	[enable_console=no]
)
AM_CONDITIONAL([ENABLE_CONSOLE], [test x$enable_console = xyes])
if test x$enable_console = xyes; then
   	AX_BOOST_THREAD
	AC_DEFINE([ENABLE_CONSOLE], 1, [define if you want a console])
	#
	# Check for Guile 1.8
	#
	PKG_CHECK_MODULES(
		[LIBGUILE],
		[guile-1.8 >= 1.8.0],
	)
fi
AC_SUBST(LIBGUILE_LIBS)

#
# Enable relative paths
#

AC_ARG_ENABLE(
	[relative-paths],
	[AS_HELP_STRING([--enable-relative-paths], [relative paths (default=no)])]
)
AM_CONDITIONAL([ENABLE_RELATIVE_PATHS], [test x$enable_relative_paths = xyes])
if test "$enable_relative_paths" = yes
then
	AC_DEFINE(
		[ENABLE_RELATIVE_PATHS], 1,
		[define if relative paths should be used]
	)
	AX_COMPUTE_STANDARD_RELATIVE_PATHS
	RELATIVE_DATADIR=$bindir_backward_relative_path/$exec_prefix_backward_relative_path/$datarootdir_forward_relative_path/$datadir_forward_relative_path
	RELATIVE_LOCALEDIR=$bindir_backward_relative_path/$exec_prefix_backward_relative_path/$datarootdir_forward_relative_path/$localedir_forward_relative_path
	AC_SUBST(RELATIVE_DATADIR)
	AC_SUBST(RELATIVE_LOCALEDIR)
fi


#
# Enable OpenAL
#

AC_ARG_ENABLE(
	[openal],
	[AS_HELP_STRING([--enable-openal], [enable OpenAL (default=no)])],
	,
	[enable_openal=no]
)
#
# Check for OpenAL, not sure what version is the minimal required
#
AM_CONDITIONAL([ENABLE_OPENAL], [test x$enable_openal = xyes])
if test x$enable_openal = xyes; then
	AC_DEFINE([ENABLE_OPENAL], 1, [define if you want to use OpenAL])
	PKG_CHECK_MODULES(
		[OPENAL],
		[openal >= 1.7.0],
	)
	AC_SUBST(OPENAL_CFLAGS)
	AC_SUBST(OPENAL_LIBS)
fi

#
# Enable experimental extras
#

AC_ARG_ENABLE(
	[experimental_extras],
	[AS_HELP_STRING(
		[--enable-experimental-extras],
		[enable experimental extras (default=no)])],
	,
	[enable_experimental_extras=no]
)
AM_CONDITIONAL(
	[ENABLE_EXPERIMENTAL_EXTRAS],
	[test x$enable_experimental_extras = xyes])
if test x$enable_experimental_extras = xyes; then
	AC_DEFINE([ENABLE_EXPERIMENTAL_EXTRAS], 1, [define if you want to use the experimental extras])
fi

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/cbe/Makefile
	src/find_bin/Makefile
	src/fonts/Makefile
	src/maps/Makefile
	src/menuentry/Makefile
	src/pics/Makefile
	src/wavs/Makefile
	po/Makefile.in
])

AC_OUTPUT
