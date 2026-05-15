#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>

// Mirrors win_fnmatch() from shim.cpp.
static int win_fnmatch(const char* glob, const char* name) {
  if( fnmatch(glob, name, FNM_NOESCAPE)==0 ) return 1;
  const char* dot_star = strrchr(glob, '.');
  if( dot_star && dot_star[1]=='*' && dot_star[2]=='\0' ) {
    size_t plen = (size_t)(dot_star - glob);
    char prefix[512];
    if( plen < sizeof(prefix) ) {
      memcpy(prefix, glob, plen); prefix[plen] = '\0';
      const char* p = plen ? prefix : "*";
      if( fnmatch(p, name, FNM_NOESCAPE)==0 ) return 1;
    }
  }
  return 0;
}

// Mirrors find_ctx_open + FindNextFile scan logic from shim.cpp.
// Tests whether a given glob pattern sees .git (and files inside it).
static void scan(const char* dir, const char* glob) {
  printf("\n--- opendir(\"%s\")  glob=\"%s\" ---\n", dir, glob);
  DIR* d = opendir(dir);
  if( !d ) { perror("opendir"); return; }
  struct dirent* ent;
  int count = 0;
  while( (ent = readdir(d)) != NULL ) {
    if( strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0 )
      continue;
    int match = win_fnmatch(glob, ent->d_name);
    printf("  %-30s  %s\n", ent->d_name, match ? "MATCH" : "no");
    if( match == 0 ) count++;
  }
  closedir(d);
  printf("  => %d match(es)\n", count);
}

int main(void) {
  // Simulate nz.exe scanning the repo root with various Windows glob patterns.
  scan(".",     "*");
  scan(".",     "*.*");

  // After seeing .git is a directory, simulate recursing into it:
  scan(".git",  "*");
  scan(".git",  "*.*");

  // Also test a dotfile name directly with fnmatch:
  printf("\nDirect fnmatch tests:\n");
  const char* names[] = { ".git", ".gitignore", "shim.cpp", "Makefile", NULL };
  const char* pats[]  = { "*", "*.*", NULL };
  for( const char** p = pats; *p; p++ ) {
    for( const char** n = names; *n; n++ ) {
      printf("  win_fnmatch(%-12s, %-15s) = %s\n",
             *p, *n, win_fnmatch(*p, *n) ? "MATCH" : "no");
    }
  }
  return 0;
}
