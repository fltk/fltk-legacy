// fl_plugin.cxx

#include <fltk/Fl.h>
#include <fltk/fl_load_plugin.h>
//#include <fltk/conf.h>
#include <fltk/vsnprintf.h>
#include <errno.h>
#include <config.h>

#ifndef WIN32

#include <unistd.h>
#include <dlfcn.h>
typedef void* DLhandle;

#else

// simulate posix on windows:
#include <windows.h>
#include <winbase.h>
typedef HINSTANCE DLhandle;
#define dlopen(a,b) LoadLibrary(a)
#define RTLD_NOW 2
#define dlsym(handle, sym) GetProcAddress(handle, sym)

#endif

#ifndef PATH_MAX
#define PATH_MAX 128
#endif

// returns address of function() (can be used as handle)
void* fl_load_plugin(const char* name, const char* function) {
#ifndef WIN32
  // do not allow plugins if this executable is setuid
  if (getuid() != geteuid()) return 0;
#endif
  if (!name || !function) return 0;
//   char name[PATH_MAX];
//   if (!conf_is_path_rooted(n)) snprintf(name, sizeof(name), "./%s", n);
//   else strncpy(name, n, sizeof(name));
  // open plugin, any errors will be printed
  DLhandle handle = dlopen(name, RTLD_NOW);
  if (!handle) {
#ifndef WIN32
    fprintf(stderr, "%s\n", dlerror());
#else
    fprintf(stderr, "%s: error loading plugin\n", name);
#endif
    return 0;
  }

  void* f = (void*)dlsym(handle, function);
  if (!f) {
#ifndef WIN32
    fprintf(stderr, "%s\n", dlerror());
#else
    fprintf(stderr, "%s: function %s missing\n", name, function);
#endif
    return 0;
  }
  return f;
}
