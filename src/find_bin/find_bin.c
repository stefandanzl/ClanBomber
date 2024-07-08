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

#include "find_bin.h"

#include <stdio.h>
#include <string.h>

#ifdef __unix__
//for dirname
#  include <libgen.h>
//for chdir, getcwd, access
#  include <unistd.h>
#endif
//#elif defined(_WIN32)

//#endif

#ifdef FB_PROC_SELF_EXE
//readlink
#  include <unistd.h>
#  include <errno.h>
#endif

#ifdef FB_SHELL
#  include <stdlib.h>
#endif

#ifdef FB_GETMODULEFILENAME
#  include <windows.h>
#endif

void fb_free(void *pointer)
{
  free(pointer);
}

//const pointer
char *fb_strdup(const char *string)
{
  int size;
  char *new_string;
  size = strlen(string);
  new_string = malloc(size * sizeof(char));
  strcpy(new_string, string);
  return new_string;
}

char *fb_path_simplify(const char *file)
{
  const char *pointer;
  char *dup_string;
  static char output[FB_BSIZE];

  output[0] = '\0';

  dup_string = fb_strdup(file);

  pointer = strtok(dup_string, "/");

  while (pointer != NULL) {
    if (strcmp(pointer, ".") == 0) {
      //printf("%s ", pointer);
    }
    else if (strcmp(pointer, "..") == 0) {
      strcpy(output, fb_dirname(output));
    }
    else {
      if (strlen(output) + strlen(pointer) >= FB_BSIZE) {
        printf("fb_path_simplify: String too big for buffer\n");
        fb_free(dup_string);
        return NULL;
      }
      sprintf(output, "%s/%s", output, pointer);
    }
    //printf("%s ", pointer);
    pointer = strtok(NULL, "/");
  }
  fb_free(dup_string);
  return output;
}

int fb_is_absolute(const char *file)
{
  //XXX check for NULL?

  //TODO Add windows code
#ifdef __unix__
  if (file[0] == '/') {
    return 1;
  }
  return 0;
#else
# error Not supported OS
#endif
}

int fb_path_valid(const char *file)
{
  if (access(file, F_OK) == 0) {
    printf("The file was found, path is probably valid\n");
    return 1;
  }
  else {
    printf("The file was not found, path is probably invalid\n");
    return 0;
  }
}

/**
 * Creates an abosulte path from a argv data.
 *
 */
const char *fb_to_absolute(const char *file)
{
  char *cwd = NULL;
  static char absolute[FB_BSIZE];

  if (fb_is_absolute(file)) {
    return file;
  }
  else {
    cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
      printf("getcwd failed, error code: %d\n", errno);
      return NULL;
    }
    if (strlen(cwd) + 1 + strlen(file) >= FB_BSIZE) {
      printf("fb_to_absolute: Too small to hold the data.\n");
      free(cwd);
      return NULL;
    }
    strcpy(absolute, cwd);
    strcat(absolute, "/");
    strcat(absolute, file);
    free(cwd);
  }
  return absolute;
}

#ifdef FB_PROC_SELF_EXE
const char *fb_method_linux()
{
  static char buffer[FB_BSIZE];
  int ret;
  ret = readlink("/proc/self/exe", buffer, FB_BSIZE);
  if (ret == -1) {
    printf("readlink failed, error code: %d\n", errno);
    return NULL;
  }
  else if (ret == FB_BSIZE) {
    printf("readlink failed, buffer too small\n");
    return NULL;
  }

  buffer[ret] = '\0';
  return buffer;
}
#endif

#ifdef FB_SHELL
/* For bash is the same as arg[0] except when the bin is in path
   then it will be the full path
*/
/* If the invoking program is run using bash then the $_ will be set
   to the first program, eg. running bash -> dash -> program will
   get the path to dash
*/
// Not reliable
const char *fb_method_shell()
{
  const char* env_path;
  env_path = getenv("_");
  if(env_path == NULL) {
    printf("Environment variable _ does not exist\n");
    return NULL;
  }
  //TODO check that env_path is a file?
  return env_path;
}
#endif

#ifdef FB_GETMODULEFILENAME
const char *fb_method_windows()
{
  static char buffer[MAX_PATH];
  int ret;

  ret = GetModuleFileName(NULL, buffer, MAX_PATH);
  if (ret == 0) {
    printf("GetModuleFileName failed, error code: %d\n", GetLastError());
    return NULL;
  }
  else if (ret == FB_BSIZE) {
    printf("GetModuleFileName failed, buffer too small\n");
    return NULL;
  }
  return buffer;
}
#endif

const char *fb_dirname(const char *file)
{
#ifdef __unix__
  if (file == NULL) {
    return NULL;
  }
  //XXX file ends with / may have an undefined behaviour
  return dirname((char *)file);
#else
# error Not supported OS
#endif
}

void fb_chdir(const char *path)
{
  //XXX What is the behaviour of chdir with NULL as a param?, it does
  //nothing in Debian
  chdir(path);
  if (chdir(path) == -1) {
    printf("fb_chdir: chdir failed, error code: %d\n", errno);
  }
}

const char *fb_method_null()
{
  return NULL;
}
