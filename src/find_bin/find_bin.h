/* This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
 * Copyright (C) 2008-2011, 2017 Rene Lopez <rsl@member.fsf.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FIND_BIN_H
#define FIND_BIN_H

/**
 * @file
 */

/**
 * Size for buffers.
 */
#define FB_BSIZE 1024

//TODO Use configure.
#define FB_PROC_SELF_EXE
#define FB_SHELL
/*#define FB_GETMODULEFILENAME*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Native way to get binary location in a Linux based OS.
 * This method doesn't work if the main thread ends as /proc/self/exe
 * will not exist anymore.
 */
const char *fb_method_linux();

/**
 * Alternative method that works in some shells.
 * Only works with some shells, eg. bash and ksh.
 * This method is not reliable.
 */
const char *fb_method_shell();

/**
 * Native method for windows
 */
const char *fb_method_windows();

const char *fb_dirname(const char *file);
void fb_chdir(const char *path);

#ifdef __linux__
# define fb_method_native fb_method_linux
#elif defined(_WIN32)
# define fb_method_native fb_method_windows
#else
  //# error Not supported OS
  const char *fb_method_null();
# define fb_method_native fb_method_null
#endif

#ifdef __cplusplus
}
#endif

#endif
