/*
Copyright (c) 2014, Anders
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the "organization" nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define _WITH_GETLINE

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <syslog.h>
#include <sys/param.h>
#include <errno.h>
#include <netdb.h>

// Global variables
char *prog_name;
char *appToRun;
//char *currentcmd;// = "hello world"; // currentcmd is basically the command that is running, which will be printed when the SIGINFO signal is received.
int verbose; //MacPorts on Darwin can print verbose messages, like make(1) does on FreeBSD.
int softupdate;
int interactive; // variable to be used to activate the -i option when using portmaster.
int portmaster_arg;
int portupgrade_arg;
int rb; //variable to be used if softwareupdate(8) requires a reboot
int sigint;
char buf[BUFSIZ];
// A "list" of a few functions used in this program.
// These are needed to avoid the conflicting types for $function erorrs during compilation.
void removeWhitespaceFromAnswer();
void askReboot();
int askUpdateFreeBSD();
void askToReadUPDATINGfile();
char *remove_substring(char *str, char *str2);
char *getOS();
void updateLinux();
int updateBaseSystem();
int cleanOldDistfiles();
int updatePkgsrc();
void updateOpenBSD();
int Search_in_File(char *fname, char *str);
void removeFile(char *name);
void listUpdates();
void checkConnection();
void exitApp(int status)
{
  if(strcmp(getOS(), "Darwin") == 0)
  {
    // Do a "port clean outdated" command on ports that are either updating
    // or about to be updated when the ctrl-c signal is caught, then
    // reset the shell title.
    int port_clean = fork();
    if(port_clean == 0)
    {
      printf("Cleaning ports...\n");
      char *port_clean_arglist[4]; 
      port_clean_arglist[0] = "port";
      port_clean_arglist[1] = "clean";
      port_clean_arglist[2] = "outdated";
      port_clean_arglist[3] = NULL;
      close(1);       /* close stdout */ 
      close(2);       /* close stderr */ 
      if(execvp(port_clean_arglist[0], port_clean_arglist) == -1)
      {
			exit(-1);
      }
    }
    else if(port_clean >= 0)
    {
      waitpid(port_clean, NULL, 0);
    }
    else
    {
     fprintf(stderr, "Could not create MacPorts process.\n");
     //return -1;
    }
     char *hjem = getenv("HOME");
    //strcat(hjem, "/ports.txt");
    remove(hjem);
    printf("\033]0;\007");
  }
  printf("\033]0;\007");
  if(status != 0){
    if(sigint)
      syslog(LOG_ERR, "One or more errors occurred while running %s on %s. Returned error code: %d (user sent SIGINT signal)\n", prog_name, getOS(), status);
    else if(status == 100) {
      syslog(LOG_ERR, "One or more errors occurred while running %s on %s. Returned error code: %d\n", prog_name, getOS(), status);
    }
    else
      syslog(LOG_ERR, "One or more errors occurred while running %s on %s. Returned error code: %d\n", prog_name, getOS(), status);
  }
  if(rb) {
    askReboot();
  }
  exit(status);
}

//Functions to handle signals sent by the operating system
// Ctrl+Z
void ctrl_z(int sig_num)
{
  signal(SIGTSTP, ctrl_z);
  fprintf(stdout, "Stopping…\n");
  // Fetches the window title
  #ifndef __sun
  FILE *pipe = popen("xdotool getactivewindow getwindowname", "r");
  fgets(buf, BUFSIZ, pipe);
  #endif
  syslog(LOG_ERR, "%s has been stopped by the user.\n", prog_name);
  kill(getpid(), SIGSTOP);
}

int p = 0;
void sigCont(int sig_num)
{
  signal(SIGCONT, sigCont);
  if(p > 0)
    p = 0;
  else if(p == 0){
    printf("\033]0;%s\007",buf);
    fprintf(stdout, "Resuming operation…\n");
    syslog(LOG_ERR, "%s is being continued.\n", prog_name);
    p++;
  }
}

// Ctrl+C
void ctrl_c(int sig_num)
{
  /* 
     catching the ctrl+c signal to reset the shell title on Darwin and FreeBSD.
     On Darwin, a bit of cleaning up is performed as well (removing a few files
     created by this tool) as well as resetting the shell title.
  */
  signal(SIGINT, ctrl_c);
  fprintf(stdout, "Quitting...\n");
  sigint = 1;
  //exitApp(1);
  exitApp(sig_num);
}

// Bus error
void sigBus(int sig_num)
{
  signal(SIGBUS, sigBus);
  syslog(LOG_ERR, "%s must quit because of a SIGBUS error.\n", prog_name);
  signal(sig_num, SIG_DFL);
  kill(getpid(), sig_num);
}

// Segmentation error
void segFault(int sig_num)
{
  signal(SIGSEGV, segFault);
  syslog(LOG_ERR, "%s must quit because of a segmentation violation.\n", prog_name);
  fprintf(stderr, "%s must quit because of a segmentation violation. If core dumps are enabled, a core dump will be created.\n", prog_name);
  signal(sig_num, SIG_DFL);
  exitApp(sig_num);
  //kill(getpid(), sig_num);
}

#ifdef SIGINFO
int prints = 0;
void sigInfo(int sig_num)
{
  signal(SIGINFO, sigInfo);
  if(prints > 0)
    prints = 0;
  else if(prints == 0)
  {
    fprintf(stdout, "\033[01;33m%s: Caught SIGINFO: Updating installed ports on %s.\nThe current command run by this program is %s.\033[00m\n", prog_name, getOS(), getprogname());
    prints++;
  }
  return;
}
#endif

/*
  Returns the operating system on which updateports is run.
*/
char* getOS()
{
  #ifdef __FreeBSD__
  return "FreeBSD";
  #elif __NetBSD__
  return "NetBSD";
  #elif __APPLE__
  return "Darwin"; // Darwin is the UNIX part of OS X.
  #elif __linux__
  return "Linux";
  #elif __sun
  return "SunOS"; // SunOS = Solaris.
  #elif __OpenBSD__
  return "OpenBSD";
  #else
  return "Other"; // Non-supported operating systems.
  #endif
}

/*
Update pkgsrc via CVS and then
update ports on NetBSD via pkgsrc and pkgtools/lintpkgsrc.
*/
int updatePkgsrc()
{
  int cvsupdate_status, cvsupdate = fork();
  if(cvsupdate == 0){
    chdir("/usr/pkgsrc");
    setenv("CVS_RSH", "ssh", 1);
    char *cvsupdate_arglist[4];
    cvsupdate_arglist[0] = "cvs";
    cvsupdate_arglist[1] = "update";
    cvsupdate_arglist[2] = "-dP";
    cvsupdate_arglist[3] = NULL;
    execvp(cvsupdate_arglist[0], cvsupdate_arglist);
  }
  else if(cvsupdate >= 0){
#ifndef __linux__
    setprogname("cvs update");
#endif
    waitpid(cvsupdate, &cvsupdate_status, 0);
    if(WIFEXITED(cvsupdate_status)){
      if(WEXITSTATUS(cvsupdate_status) != 0){
	fprintf(stderr, "There is a problem updating the pkgsrc system. Aborting. The returned status code was %d\n", WEXITSTATUS(cvsupdate_status));
	exitApp(WEXITSTATUS(cvsupdate_status));
      }
    }
  }

  // Use lintpkgsrc to check for port updates.
  int lint_status, lint = fork();
  if(lint == 0){
    char *lint_args[3];
    lint_args[0] = "lintpkgsrc";
    lint_args[1] = "-i";
    lint_args[2] = NULL;
    execvp(lint_args[0], lint_args);
  }

  else if(lint >= 0){
#ifndef __linux__
    setprogname("lintpkgsrc -i");
#endif
    waitpid(lint, &lint_status, 0);
    if(WIFEXITED(lint_status)){
      if(WEXITSTATUS(lint_status) != 0){
	fprintf(stderr, "Something has gone wrong when executing lintpkgsrc and the updating process has been terminated. The returned status code was %d\n", WEXITSTATUS(lint_status));
	exitApp(WEXITSTATUS(lint_status));
      }
    }
  }
  // Update installed ports:
  int make_status, make = fork();
  if(make == 0){
    chdir("/usr/pkgsrc");
    char *make_args[3];
    make_args[0] = "make";
    make_args[1] = "update";
    make_args[2] = NULL;
    execvp(make_args[0], make_args);
  }
  else if(make >= 0){
#ifndef __linux__
    setprogname("make update");
#endif
    waitpid(make, &make_status, 0);
    if(WIFEXITED(make_status)){
      if(WEXITSTATUS(make_status) != 0){
	fprintf(stderr, "Something has gone wrong while running the command \"make update.\" The returned error code was %d\n", WEXITSTATUS(make_status));
	exitApp(WEXITSTATUS(make_status));
      }
    }
  }
  return 0;
}


/*
checkExec checks if the provided filename is an executable program.
1 = OK.
0 = failure.
That way, we can just do if(checkExec(filename)) intstead of having to
do if(checkExec(filename) == 0) or if(!checkExec(filename)).
*/
int checkExec(char* filename)
{
  if(access(filename, F_OK | X_OK) == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void askUpdateTool()
{
  // Creating a few children processes, of cource depending on what is installed.
  if(checkExec("/usr/local/sbin/portmaster") && checkExec("/usr/local/sbin/portupgrade"))
  {
    // Ask the user which tool he'd like to use...
    printf("Both utilities are installed.\n");
    printf("Both /usr/local/sbin/portmaster and /usr/local/sbin/portupgrade seem to be installed. Which of those tools would you like to use?\n");
    printf("Type 'pm' for portmaster or 'pu' for portupgrade: ");
    char *ut; // ut = utility
    size_t ut_linecap = 0;
    ut = (char *)malloc(ut_linecap +1);
    if(getline(&ut, &ut_linecap, stdin) == -1)
    {
      fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
      exit(-1);
    }
    removeWhitespaceFromAnswer(ut);
    long ut_length = strlen(ut);
    if(ut_length != 3)
    {
      printf("The answer can only contain 2 letters. Length of current answer: %ld\n", ut_length -1);
      askUpdateTool();
    }
    else
    {
      /*The following piece of code removes the newline from the string called "ut":*/
      char *tmp = strstr(ut, "\t");
      while((tmp = strstr(ut, "\n")) != NULL)
      {
	long len = strlen(ut);
	memmove(tmp, tmp +1, len);
      }
      //end of newline removal.
      if(strcmp("pm", ut) == 0)
      {
	printf("Will use Portmaster.\n");
	appToRun = "/usr/local/sbin/portmaster";
      }
      else if(strcmp("pu", ut) == 0)
      {
	printf("Will use Portupgrade.\n");
	appToRun = "/usr/local/sbin/portupgrade";
      }
      else
      {
	printf("Invalid answer.\n");
      }
    }
  }
  else if(checkExec("/usr/local/sbin/portmaster") && !checkExec("/usr/local/sbin/portupgrade"))
  {
    if(portmaster_arg)
      appToRun = "/usr/local/sbin/portmaster";
  }
  else if(!checkExec("/usr/local/sbin/portmaster") && checkExec("/usr/local/sbin/portupgrade"))
  {
    if(portupgrade_arg)
      appToRun = "/usr/local/sbin/portupgrade";
  }
  else
  {
    /*
      Assume we're going to use FreeBSD's PKG tool.
     */
    appToRun = "/usr/sbin/pkg";
  }
}
#ifndef __linux__
int runPortsnap()
{
  int portsnap_status;
  int portsnap = fork();
  if(portsnap == 0)
  {
    char *portsnap_arglist[4];
    portsnap_arglist[0] = "/usr/sbin/portsnap";
    portsnap_arglist[1] = "fetch";
    portsnap_arglist[2] = "update";
    portsnap_arglist[3] = NULL;
    execvp(portsnap_arglist[0], portsnap_arglist);
  }
  else if(portsnap >= 0)
  {
    setprogname("portmaster fetch update");
    printf("\033]0;Updating the ports tree by running /usr/sbin/portmaster fetch update\007");
    printf("Updating the ports tree by running /usr/sbin/portmaster fetch update…\n");
    waitpid(portsnap, &portsnap_status, 0);
    if(WIFEXITED(portsnap_status))
    {
      if(WEXITSTATUS(portsnap_status) != 0)
      {
	fprintf(stderr, "Something has gone wrong and the updating process has been termiated. The returned status code was %d.\n",WEXITSTATUS(portsnap_status));
	exitApp(WEXITSTATUS(portsnap_status));
      }
    }
  }
  return 0;
}
#endif

void listUpdates()
{
  /*
    Tar en mer "lettvindt" løsning og bruker systemkallet
    system (const char *string) til å skrive ut utdataen for kommandoene
    pkg version | grep "<" (| wc -l).
   */
  system("pkg version | grep \"<\" | wc -l > /.availUpdates.txt");
  if(Search_in_File("/.availUpdates.txt", "       0") == 0) {
    fprintf(stdout, "There are no updates available.\n");
    removeFile("/.availUpdates.txt");
    if(rb)
      askReboot();
    exitApp(0); // Velger å ikke ta denne kodesnutten i en else, siden brukeren kan svare nei på spørsmål om omstart. 
  }
  removeFile("/.availUpdates.txt");
  fprintf(stdout, "The following ports will be updated:\n");
  int res = system("rmoldpackages_updateports");
  if(res != 0)
    exitApp(res);
    
}

int updateFreeBSD()
{
  int res = 0;
  #ifndef __linux__
  printf("\033]0;Updating ports system\007");
  int portupgrade_status, portFetch_status, pkg_status, portmaster_status, portsclean_status;
  if(strcmp(appToRun, "/usr/local/sbin/portmaster") != 0 && strcmp(appToRun, "/usr/local/sbin/portupgrade") != 0)
  {
    askUpdateTool();
  }
  if(softupdate == 0)
    res = updateBaseSystem();
  if (res != 0)
    return res;
  if(strcmp(appToRun, "/usr/local/sbin/portmaster") == 0)
  {
    res = runPortsnap();
    if(res != 0)
      return res;
    if(softupdate == 0)
      askToReadUPDATINGfile();
  }
    // I am now assuming that appToRun = /usr/local/sbin/portmaster or appToRun = /usr/local/sbin/portupgrade
  else if(strcmp(appToRun, "/usr/local/sbin/portupgrade") == 0)
  {
    runPortsnap();
    if(res != 0)
      return res;
    if(softupdate == 0)
      askToReadUPDATINGfile();
  }
  if(strcmp(appToRun, "/usr/local/sbin/portmaster") == 0)
  {
    if(interactive)
    {
      int portmaster = fork();
      if(portmaster == 0) {
	char *portmaster_arglist[3];
	portmaster_arglist[0] = "/usr/local/sbin/portmaster";
	portmaster_arglist[1] = "-DBCaig";
	portmaster_arglist[2] = NULL;
	execvp(portmaster_arglist[0], portmaster_arglist);
      }
      else if(portmaster >= 1){
	setprogname("portmaster -DBCaig");
	waitpid(portmaster, &portmaster_status, 0);
	if(WIFEXITED(portmaster_status)){
	  if(WEXITSTATUS(portmaster_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portmaster_status));
	    exitApp(WEXITSTATUS(portmaster_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Could not create portmaster process.\n");
	return -1;
      }
    }
    else {
      int portmaster = fork();
      if(portmaster == 0){
	char *portmaster_arglist[3];
	portmaster_arglist[0] = "/usr/local/sbin/portmaster";
	portmaster_arglist[1] = "-DBCag";
	portmaster_arglist[2] = NULL;
	execvp(portmaster_arglist[0], portmaster_arglist);
      }
      else if(portmaster >= 1){
	setprogname("portmaster -DBCag");
	waitpid(portmaster, &portmaster_status, 0);
	if(WIFEXITED(portmaster_status)){
	  if(WEXITSTATUS(portmaster_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portmaster_status));
	    exitApp(WEXITSTATUS(portmaster_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Could not create portmaster process.\n");
	return -1;
      }
    }
    //printf("\033]0;\007");
    system("rmoldpackages_updateports removeOld");
    cleanOldDistfiles();
  }
  else if(strcmp(appToRun, "/usr/local/sbin/portupgrade") == 0)
  {
    if(interactive){
      printf("\033]0;Fetching new distfiles using Portupgrade\007");
      fprintf(stdout, "Fetching new distfiles using Portupgrade…\n");
      int portFetch = fork();
      if(portFetch == 0){
	char *portFetch_arglist[3];
	portFetch_arglist[0] = "/usr/local/sbin/portupgrade";
	portFetch_arglist[1] = "-Fa";
	portFetch_arglist[2] = NULL;
	execvp(portFetch_arglist[0], portFetch_arglist);
      }
      else if(portFetch >= 1){
	setprogname("portupgrade -Fa");
	waitpid(portFetch, &portFetch_status, 0);
	if(WIFEXITED(portFetch_status)){
	  if(WEXITSTATUS(portFetch_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portFetch_status));
	    exitApp(WEXITSTATUS(portFetch_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Failed to create portupgrade process.\n");
	return -1;
      }
      printf("\033]0;Compiling updated ports using Portupgrade\007");
      fprintf(stdout, "Compiling updated ports using Portupgrade.\n");
      int portupgrade = fork();
      if(portupgrade == 0){
	char *portupgrade_arglist[3];
	portupgrade_arglist[0] = "/usr/local/sbin/portupgrade";
	portupgrade_arglist[1] = "-api";
	portupgrade_arglist[2] = NULL;
	execvp(portupgrade_arglist[0], portupgrade_arglist);
      }
      else if(portupgrade >= 1){
	setprogname("portupgrade -ap");
	waitpid(portupgrade, &portupgrade_status, 0);
	if(WIFEXITED(portupgrade_status)){
	  if(WEXITSTATUS(portupgrade_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portupgrade_status));
	    exitApp(WEXITSTATUS(portupgrade_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Failed to create portupgrade process.\n");
	return -1;
      }
    }
    else if(verbose){
      printf("\033]0;Fetching new distfiles using Portupgrade\007");
      fprintf(stdout, "Fetching new distfiles using Portupgrade\n");
      
      int portFetch = fork();
      if(portFetch == 0){
	char *portFetch_arglist[3];
	portFetch_arglist[0] = "/usr/local/sbin/portupgrade";
	portFetch_arglist[1] = "-Fa";
	portFetch_arglist[2] = NULL;
	execvp(portFetch_arglist[0], portFetch_arglist);
      }
      else if(portFetch >= 1){
	setprogname("portupgrade -Fa");
	waitpid(portFetch, &portFetch_status, 0);
	if(WIFEXITED(portFetch_status)){
	  if(WEXITSTATUS(portFetch_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portFetch_status));
	    exitApp(WEXITSTATUS(portFetch_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Failed to create portupgrade process.\n");
	return -1;
      }
      printf("\033]0;Compiling updated ports using Portupgrade\007");
      fprintf(stdout, "Compiling updated ports using Portupgrade.\n");
      int portupgrade = fork();
      if(portupgrade == 0){
	char *portupgrade_arglist[3];
	portupgrade_arglist[0] = "/usr/local/sbin/portupgrade";
	portupgrade_arglist[1] = "-apv";
	portupgrade_arglist[2] = NULL;
	execvp(portupgrade_arglist[0], portupgrade_arglist);
      }
      else if(portupgrade >= 1){
	setprogname("portupgrade -apv");
	waitpid(portupgrade, &portupgrade_status, 0);
	if(WIFEXITED(portupgrade_status)){
	  if(WEXITSTATUS(portupgrade_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portupgrade_status));
	    exitApp(WEXITSTATUS(portupgrade_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Failed to create portupgrade process.\n");
	return -1;
      }
    }
    else{
      printf("\033]0;Fetching new distfiles using Portupgrade\007");
      fprintf(stdout, "Fetching new distfiles using Portupgrade\n");
      
      int portFetch = fork();
      if(portFetch == 0){
	char *portFetch_arglist[3];
	portFetch_arglist[0] = "/usr/local/sbin/portupgrade";
	portFetch_arglist[1] = "-Fa";
	portFetch_arglist[2] = NULL;
	execvp(portFetch_arglist[0], portFetch_arglist);
      }
      else if(portFetch >= 1){
	setprogname("portupgrade -Fa");
	waitpid(portFetch, &portFetch_status, 0);
	if(WIFEXITED(portFetch_status)){
	  if(WEXITSTATUS(portFetch_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portFetch_status));
	    exitApp(WEXITSTATUS(portFetch_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Failed to create portupgrade process.\n");
	return -1;
      }
      printf("\033]0;Compiling updated ports using Portupgrade\007");
      fprintf(stdout, "Compiling updated ports using Portupgrade.\n");
      int portupgrade = fork();
      if(portupgrade == 0){
	char *portupgrade_arglist[3];
	portupgrade_arglist[0] = "/usr/local/sbin/portupgrade";
	portupgrade_arglist[1] = "-ap";
	portupgrade_arglist[2] = NULL;
	execvp(portupgrade_arglist[0], portupgrade_arglist);
      }
      else if(portupgrade >= 1){
	setprogname("portupgrade -ap");
	waitpid(portupgrade, &portupgrade_status, 0);
	if(WIFEXITED(portupgrade_status)){
	  if(WEXITSTATUS(portupgrade_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portupgrade_status));
	    exitApp(WEXITSTATUS(portupgrade_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Failed to create portupgrade process.\n");
	return -1;
      }
    }
    //printf("\033]0;\007");
    system("rmoldpackages_updateports removeOld");
    cleanOldDistfiles();
  }
  else if(strcmp(appToRun, "/usr/sbin/pkg") == 0)
  {
    /*
      Let's assume that we are going to use FreeBSD's PKG tools.
    */
    int pkg = fork();
    if(pkg == 0)
    {
      char *pkg_arglist[3];
      pkg_arglist[0] = "/usr/sbin/pkg";
      pkg_arglist[1] = "upgrade";
      pkg_arglist[2] = NULL;
      execvp(pkg_arglist[0], pkg_arglist);
    }
    else if(pkg >= 1)
    {
      setprogname("pkg upgrade");
      printf("\033]0;Updating installed applications by running /usr/sbin/pkg upgrade…\007");
      printf("Updating installed applications by running /usr/sbin/pkg upgrade…\n");
      waitpid(pkg, &pkg_status, 0);
      if(WIFEXITED(pkg_status)){
	if(WEXITSTATUS(pkg_status) != 0){
	  printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(pkg_status));
	  exitApp(WEXITSTATUS(pkg_status));
	}
      }
    }
    else
    {
      fprintf(stderr, "Failed to create pkg process.\n");
      return -1;
    }
  }
  if(rb)
  {
    // insert code here…
    askReboot();
  }
  return 0;
  #endif
}

// Clean out (remove) old, unused distfiles to save up space
#ifndef __linux__
int cleanOldDistfiles()
{
  //printf("\n");
  printf("Do you want to remove old and unused distfiles (if there are any)? (Y/n) ");
  char *ans;
  size_t ans_linecap = 0;
  ans = (char *)malloc(ans_linecap +1);
  if(getline(&ans, &ans_linecap, stdin) == -1) {
    fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
    exitApp(-1);
  }
  char *tmp = strstr(ans, "\t");
  while((tmp = strstr(ans, "\n")) != NULL) {
    long len = strlen(ans); // lengden på svaret som brukeren ga
    memmove(tmp, tmp +1, len); // kopierer strengen
  }
  // Henter ut den nye lengden:
  long len = strlen(ans);
  if(len > 0){
   removeWhitespaceFromAnswer();
  }
  if(strncmp("y", ans, 1) == 0 || strncmp("Y", ans, 1) == 0 || strncmp("", ans, 1) == 0){
    int portupgrade_status, portmaster_status, portsclean_status;
    if(strcmp(appToRun, "/usr/local/sbin/portmaster") == 0){
      fprintf(stdout,"Cleaning old and unused distfiles using Portmaster.\n");
      int portmaster = fork();
      if(portmaster == 0){
	char *portmaster_arglist[4];
	portmaster_arglist[0] = "/usr/local/sbin/portmaster";
	portmaster_arglist[1] = "-y";
	portmaster_arglist[2] = "--clean-distfiles";
	portmaster_arglist[3] = NULL;
	execvp(portmaster_arglist[0], portmaster_arglist);
      }
      else if(portmaster >= 1){
	setprogname("portmaster -y --clean-distfiles");
	waitpid(portmaster, &portmaster_status, 0);
	if(WIFEXITED(portmaster_status)){
	  if(WEXITSTATUS(portmaster_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portmaster_status));
	    exitApp(WEXITSTATUS(portmaster_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Could not create portmaster process.\n");
	return -1;
      }
    }
    else if(strcmp(appToRun, "/usr/local/sbin/portupgrade") == 0){
      fprintf(stdout, "Cleaning old and unused distfiles using Portupgrade.\n");
      int portsclean = fork();
      if(portsclean == 0){
	char *portsclean_arglist[3];
	portsclean_arglist[0] = "/usr/local/sbin/portsclean";
	portsclean_arglist[1] = "-CDD";
	portsclean_arglist[2] = NULL;
	execvp(portsclean_arglist[0], portsclean_arglist);
      }
      else if(portsclean >= 1){
	setprogname("portsclean -CDO");
	waitpid(portsclean, &portsclean_status, 0);
	if(WIFEXITED(portsclean_status)){
	  if(WEXITSTATUS(portsclean_status) != 0){
	    printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(portsclean_status));
	    exitApp(WEXITSTATUS(portsclean_status));
	  }
	}
      }
      else{
	fprintf(stderr, "Could not create portsclean process.\n");
	return -1;
      }
    }
  }
  else if(strncmp("n", ans, 1) == 0 || strncmp("N", ans, 1) == 0) {
    return 0;
  }
  else {
    fprintf(stdout, "Please type y (yes) or n (no).\n");
    cleanOldDistfiles();
  }
  return 0;
}
#endif
void askToReadUPDATINGfile()
{
  printf("\033]0;Updating %s base and ports system\007", getOS());
  //printf("\n");
  printf("Would you like to read /usr/ports/UPDATING?(Y/n) ");
  char *readUPDATINGfile;
  size_t updatingfile_linecap = 0;
  readUPDATINGfile = (char *)malloc(updatingfile_linecap +1);
  if(getline(&readUPDATINGfile, &updatingfile_linecap, stdin) == -1)
  {
    fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
    exit(-1);
  }
  char *tmp = strstr(readUPDATINGfile, "\t");
  while((tmp = strstr(readUPDATINGfile, "\n")) != NULL)
  {
    long len = strlen(readUPDATINGfile);
    memmove(tmp, tmp +1, len);
  }
  long ansUPDATINGfile_length = strlen(readUPDATINGfile);
  if(ansUPDATINGfile_length > 0){
    // Fjerner mellomrom fra tekststrengen.
    char *str;
    str=readUPDATINGfile;
    while(*str == ' ') str++;
    if(str != readUPDATINGfile) memmove(readUPDATINGfile, str, strlen(str)+1);
  }
  if(strncmp("y", readUPDATINGfile, 1) == 0 || strncmp("Y", readUPDATINGfile, 1) == 0 || strncmp("", readUPDATINGfile, 1) == 0)
  {
    int updating = fork();
    if(updating == 0)
    {
      char *updating_arglist[3];
      updating_arglist[0] = "/usr/bin/less";
      updating_arglist[1] = "/usr/ports/UPDATING";
      updating_arglist[2] = NULL;
      execvp(updating_arglist[0], updating_arglist);
    }
    else if(updating >= 0)
    {
      waitpid(updating, NULL, 0);
    }
    else
    {
      fprintf(stderr, "Process creation failed.\n");
      exit(-2);
    }
    printf("Do you need to take manual action?(y/n) ");
    char *updateAction;
    size_t updateAction_linecap = 0;
    updateAction = (char *)malloc(updateAction_linecap +1);
    if(getline(&updateAction, &updateAction_linecap, stdin) == -1)
    {
      fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
      exit(-1);
    }
    char *upd_tmp = strstr(updateAction, "\t");
    while((upd_tmp = strstr(updateAction, "\n")) != NULL)
    {
		long upd_len = strlen(updateAction);
		memmove(upd_tmp, upd_tmp +1, upd_len);
    }
    long len = strlen(updateAction);
    if(len > 0){
      // Fjerner mellomrom fra tekststrengen.
      char *str;
      str=updateAction;
      while(*str == ' ') str++;
      if(str != updateAction) memmove(updateAction, str, strlen(str)+1);
    }
    if(strncmp("y", updateAction, 1) == 0 || strncmp("Y", updateAction, 1) == 0 || strncmp("", updateAction, 1) == 0)
    {
      printf("Type the command(s) that need(s) to be executed on the prompt below. You can separate multiple sommands by typing && or ; between the commands (e.g. echo hello && echo hey).\n");
      printf("Command(s) to be executed: ");
      char *command;
      size_t command_linecap = 0;
      command = (char *)malloc(command_linecap + 1);
      if(getline(&command, &command_linecap, stdin) == -1)
      {
			fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
			exit(-1);
      }
      //using the system() system call to execute nessesary commands. of course this is a bit dangerous, but for now I like to keep things simple...
      system(command);
      askToReadUPDATINGfile();
    }
    else if(strncmp("n", updateAction, 1) == 0 || strncmp("N", updateAction, 1) == 0){
      listUpdates();
      return;
    }
    else
    {
      printf("Please type y for 'yes' or n for 'no'.\n");
      askToReadUPDATINGfile();
    }
  }
  else if(strncmp("n", readUPDATINGfile, 1) == 0 || strncmp("N", readUPDATINGfile, 1) == 0){
    listUpdates();
    return;
  }
  else
  {
    printf("Please type y for yes or n for no.\n");
    askToReadUPDATINGfile();
  }
}

void removeFile(char *name)
{
  remove(name);
}

int updateDarwin()
{
  #ifndef __linux__
  int rerun=0;
  // this assumes that the MacPort utility has been installed to /opt/local/bin/port. The same will go for Fink and HomeBrew when I add support for those tools as well.
  //printf("%s\n", strcat(getenv("HOME"), "/ports.txt"));
  char *hjem = getenv("HOME");
  strcat(hjem, "/ports.txt");
  if(checkExec("/opt/local/bin/port"))
  {
    appToRun = "/opt/local/bin/port";
  }
  else if(checkExec("/usr/local/bin/port"))
  {
    appToRun = "/usr/local/bin/port";
  }
  else
  {
    fprintf(stderr, "Plese install MacPorts to /opt/local or /usr/local.\n");
    return 1;
  }
  if(verbose == 1)
  {
    int selfupdate = fork();
    if(selfupdate == 0)
    {
      char *selfupdate_arglist[4];
      selfupdate_arglist[0] = appToRun;
      selfupdate_arglist[1] = "-v";
      selfupdate_arglist[2] = "selfupdate";
      selfupdate_arglist[3] = NULL;
      int i =0;
      execvp(selfupdate_arglist[0], selfupdate_arglist);
    }
    else if(selfupdate >= 1)
    {
      setprogname("port -v selfupdate");
      waitpid(selfupdate, NULL, 0);
    }
    else
    {
      fprintf(stderr, "Failed to create a MacPorts process.\n");
      return -1;
    }
    
    // Now, let's list the outdated ports:
    FILE *portsFile;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    //portsFile = fopen("$HOME/ports.txt", "r");
    //portsFile = fopen(strcat(getenv("HOME"), "/ports.txt"), "r");
    portsFile = fopen(hjem, "r");
    int numberOfPorts = 0, totalNumberOfPorts = 0;
    if(portsFile == NULL)
    {
      portsFile = fopen(hjem, "wb");
      if(portsFile == NULL)
      {
			fprintf(stderr, "Something has gone wrong...\n");
			return -1;
      }
    }
    //system("port list outdated &");
    char portCommand[100] = "port list outdated | /usr/bin/tee -a ";
    strcat(portCommand, hjem);
    strcat(portCommand, " &>/dev/null");
    system(portCommand);
    fclose(portsFile);
    portsFile = fopen(hjem, "r");
    while((read = getline(&line, &len, portsFile)) != -1)
    {
      totalNumberOfPorts ++;
    }
    printf("Total number of ports to be updated: %d\n", totalNumberOfPorts);
    printf("\033]0;%d ports to be updated\007", totalNumberOfPorts);
    fclose(portsFile);
    //fopen("/Users/andersbo/ports.txt", "r");
    fopen(hjem, "r");
    //char *s, *new_string = NULL;
    int updatedPorts = 1;
    while((read = getline(&line, &len, portsFile)) != -1)
    {
      printf("Updating port %d of %d\n", updatedPorts, totalNumberOfPorts);
      char *tmp = strstr(line, "\t");
      while((tmp = strstr(line, "\n")) != NULL)
      {
	long len = strlen(line);
	memmove(tmp, tmp +1, len);
      }
      char *c = line;
      char *s = NULL;
      //char c[strlen(line)] = " ";
      char *d = line;
      while(*d != 0)
      {
	*c=*d++;
	if(*c != ' ')
	  c++;
      }
      *c=0;
      //char *s;
      /*char **buf = line;
      s = strchr(buf, '@');
      printf("Found a @ at %s\n", s);*/
      char find = '@';
      const char *ptr = strchr(line, find);
      if(ptr) 
      {
	int index = ptr - line;
	line[index] = '\0';
      }
      printf("\033]0;Updating port %s (%d of %d)\007", line, updatedPorts, totalNumberOfPorts);
      fprintf(stdout, "Updating %s\n", line);
      // Now let's update each port individually.
      int status;
      int update = fork();
      if(update == 0)
      {
	char *update_arglist[5];
	update_arglist[0] = appToRun;
	update_arglist[1] = "-vn";
	update_arglist[2] = "upgrade";
	update_arglist[3] = line;
	update_arglist[4] = NULL;
	execvp(update_arglist[0], update_arglist);
      }
      else if(update >= 1)
      {
	setprogname("port -v upgrade outdated");
	waitpid(update, &status, 0);
	if(WIFEXITED(status))
	{
	  if(WEXITSTATUS(status) != 0)
	  {
	    fclose(portsFile);
	    //printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(status));
	    //exitApp(WEXITSTATUS(status));
	    rerun = WEXITSTATUS(status);
	    //updatedPorts++;
	    continue;
	  }
	  fprintf(stdout, "Done with %s.\n", line);
	}
      }
      else
      {
	fprintf(stderr, "Could not create process to run MacPorts.\n");
	return -1;
      }
      fprintf(stdout, "Updated %d of %d ports.\n", updatedPorts, totalNumberOfPorts);
      updatedPorts++;
    }
    if(line)
      free(line);
    fclose(portsFile);
     // And then, let's remove the ports.txt file:
    char *hjem = getenv("HOME");
    //strcat(hjem, "/ports.txt");
    removeFile(hjem);
    printf("\033]0;\007");
  }
  else
  {
    int selfupdate = fork();
    int selfupdate_status = 0;
    if(selfupdate == 0)
    {
      char *selfupdate_arglist[3];
      selfupdate_arglist[0] = appToRun;
      selfupdate_arglist[1] = "selfupdate";
      selfupdate_arglist[2] = NULL;
      int i =0;
      execvp(selfupdate_arglist[0], selfupdate_arglist);
    }
    else if(selfupdate >= 1)
    {
      setprogname("port selfupdate");
      waitpid(selfupdate, &selfupdate_status, 0);
      if(WIFEXITED(selfupdate_status))    
      {
	if(selfupdate_status != 0)
	{
	  fprintf(stderr, "The command \"port selfupdate\" exited with status: %d\n", WEXITSTATUS(selfupdate_status));
	}
      }
    }
    else
    {
      fprintf(stderr, "Failed to create a MacPorts process.\n");
      return -1;
    }
    
    // Now, let's list the outdated ports:
    FILE *portsFile;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    //portsFile = fopen("$HOME/ports.txt", "r");
    //portsFile = fopen(strcat(getenv("HOME"), "/ports.txt"), "r");
    portsFile = fopen(hjem, "r");
    int numberOfPorts = 0, totalNumberOfPorts = 0;
    if(portsFile == NULL)
    {
      portsFile = fopen(hjem, "wb");
      if(portsFile == NULL)
      {
	fprintf(stderr, "Something has gone wrong...\n");
	return -1;
      }
    }
    //system("port list outdated &");
    char portCommand[100] = "port list outdated | /usr/bin/tee -a ";
    strcat(portCommand, hjem);
    strcat(portCommand, " &>/dev/null");
    system(portCommand);
    fclose(portsFile);
    portsFile = fopen(hjem, "r");
    while((read = getline(&line, &len, portsFile)) != -1)
    {
      printf("read.\n");
      totalNumberOfPorts ++;
    }
    printf("Total number of ports to be updated: %d\n", totalNumberOfPorts);
    printf("\033]0;%d ports to be updated\007", totalNumberOfPorts);
    fclose(portsFile);
    fopen("/Users/andersbo/ports.txt", "r");
    //char *s, *new_string = NULL;
    int updatedPorts = 1;
    while((read = getline(&line, &len, portsFile)) != -1)
    {
      printf("Updating port %d of %d\n", updatedPorts, totalNumberOfPorts);
      char *tmp = strstr(line, "\t");
      while((tmp = strstr(line, "\n")) != NULL)
      {
	long len = strlen(line);
	memmove(tmp, tmp +1, len);
      }
      char *c = line;
      char *s = NULL;
      //char c[strlen(line)] = " ";
      char *d = line;
      while(*d != 0)
      {
	*c=*d++;
	if(*c != ' ')
	  c++;
      }
      *c=0;
      //char *s;
      /*char **buf = line;
      s = strchr(buf, '@');
      printf("Found a @ at %s\n", s);*/
      char find = '@';
      const char *ptr = strchr(line, find);
      if(ptr) 
      {
	int index = ptr - line;
	line[index] = '\0';
      }
      printf("\033]0;Updating port %s (%d of %d)\007", line, updatedPorts, totalNumberOfPorts);
      fprintf(stdout, "Updating %s\n", line);
      // Now let's update each port individually.
      int update = fork();
      int status;
      if(update == 0)
      {
	char *update_arglist[5];
	update_arglist[0] = appToRun;
	update_arglist[1] = "-n";
	update_arglist[2] = "upgrade";
	update_arglist[3] = line;
	update_arglist[4] = NULL;
	execvp(update_arglist[0], update_arglist);
	waitpid(update, &status, 0);
      }
      else if(update >= 1)
      {
	setprogname("port upgrade outdated");
	waitpid(update, &status, 0);
	if(WIFEXITED(status)){
	  if(WEXITSTATUS(status) != 0){
	    fclose(portsFile);
	    //printf("Something has gone wrong and the updating process has been stopped.\n The returned status code was: %d\n", WEXITSTATUS(status));
	    //exitApp(WEXITSTATUS(status));
	    rerun =  WEXITSTATUS(status);
	    continue;
	  }
	  fprintf(stdout, "Done with %s.\n", line);
	}
      }
      else
      {
	fprintf(stderr, "Could not create process to run MacPorts.\n");
	return -1;
      }
      fprintf(stdout, "Updated %d of %d ports.\n", updatedPorts, totalNumberOfPorts);
      updatedPorts++;
    }
    if(line)
      free(line);
    fclose(portsFile);
     // And then, let's remove the ports.txt file:
    char *hjem = getenv("HOME");
    //strcat(hjem, "/ports.txt");
    removeFile(hjem);
    printf("\033]0;\007");
  }
  if(rerun != 0)
  {
    printf("Something has gone wrong and the updating process has been restarteded.\nThic can happen if a dependency does not get updated before a port that depends on it.\nIf the script seems to be running in an infinitely loop, press ctrl-c and type port upgrade outdated.\n The returned status code was: %d\n", rerun);
    sleep(5);
    updateDarwin();
  }
  if(rb)
  {
    // insert code here…
    askReboot();
  }
  return 0;
  #endif
}

void askReboot()
{
  if(strcmp(getOS(), "Darwin") == 0){
    printf("\033[0;30mOne or more updates installed by softwareupdate requires a system reboot. Warning: If there are any unsaved changes, please make sure to save those changes BEFORE pressing y to initiate the reboot process.\033[0m\n");
  }
  else if(strcmp(getOS(), "FreeBSD") == 0){
    printf("\033[1mA newer version of the FreeBSD kernel seems to have been installed. In order to use this new minor updated version, a reboot is required. Warning: If there are any unsaved changes, please make sure to save those changes BEFORE pressing y to initiate the reboot process\033[0m.\n");
  }
  printf("Would you like to reboot your computer now? (Y/n) ");
  char *ans;
  size_t ans_linecap = 0;
  ans = (char *)malloc(ans_linecap +1);
  if(getline(&ans, &ans_linecap, stdin) == -1)
  {
    fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
    exit(-1);
  }
  char *tmp = strstr(ans, "\t");
  while((tmp = strstr(ans, "\n")) != NULL)
  {
    long len = strlen(ans);
    memmove(tmp, tmp +1, len);
  }
  long ansUPDATINGfile_length = strlen(ans);
  if(ansUPDATINGfile_length > 0){
    removeWhitespaceFromAnswer();
  }
  if(strncmp("y", ans, 1) == 0 || strncmp("Y", ans, 1) == 0 || strncmp("", ans, 1) == 0)
  {
    fprintf(stdout, "Rebooting your computer by running \"/sbin/shutdown -r now\"\n");
    system("/sbin/shutdown -r now");
  }
  else if(strncmp("n", ans, 1) == 0 || strncmp("N", ans, 1) == 0)
  {
    return;
  }
  else
  {
    printf("Please answer by typing y or n and then press return.\n");
    askReboot();
  }
}

int Search_in_File(char *fname, char *str) 
{
  FILE *fp;
  int line_num = 1;
  int find_result = 0;
  char temp[512];
  
  
  if((fp=fopen(fname, "r")) == NULL) 
    {
      printf("There is something wrong!\n");
      return(-1);
    }
  
  while(fgets(temp, 512, fp) != NULL) {
    if((strstr(temp, str)) != NULL) {
      //printf("A match found on line: %d\n", line_num);
      //printf("\n%s\n", temp);
      find_result++;
    }
    line_num++;
  }
  
  if(find_result == 0) {
    //printf("\nSorry, couldn't find a match.\n");
    if(fp) {
      fclose(fp);
    }
    return 1;
  }
  
  //Close the file if still open.
  if(fp) {
    fclose(fp);
  }
  return(0);
}


// updateBaseSystem() is only supposed to be run on Darwin and FreeBSD.
// On other systems, like SunOS (Solaris) and Linux, we use
// pkg and apt-get respectively to achieve the same.
int updateBaseSystem()
{
  printf("\033]0;Updating %s operating system and installed applications\007", getOS());
  fprintf(stdout, "Updating %s operating system and installed applications…\n", getOS());
  //printf("\n");
  /*#ifdef SIGINFO
  signal(SIGINFO, sigInfo);
  #endif*/
  int status;
  #ifndef __linux__
  char *sys_home = getenv("HOME");
  if(strcmp(getOS(), "Darwin") == 0)
  {
    if(softupdate == 0)
    {
      printf("Would you like to use softwareupdate(8) to update the base system?(Y/n) ");
      char *ans_baseSystem;
      size_t ans_baseSystem_linecap = 0;
      ans_baseSystem = (char *)malloc(ans_baseSystem_linecap +1);
      if(getline(&ans_baseSystem, &ans_baseSystem_linecap, stdin) == -1)
      {
	fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
	exit(-1);
      }
      char *tmp = strstr(ans_baseSystem, "\t");
      while((tmp = strstr(ans_baseSystem, "\n")) != NULL){
	long len = strlen(ans_baseSystem);
	memmove(tmp, tmp +1, len);
      }
      long ansUPDATINGfile_length = strlen(ans_baseSystem);
      if(ansUPDATINGfile_length > 0){
	removeWhitespaceFromAnswer();
      }
      if(strncmp("y", ans_baseSystem, 1) == 0 || strncmp("Y", ans_baseSystem, 1) == 0 || strncmp("", ans_baseSystem, 1) == 0){
	FILE* softUpd;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *home = getenv("HOME");
	strcat(home, "/.softUpd.txt");
	softUpd = fopen(home,"w");
	fclose(softUpd);
	system("softwareupdate -l &");
	int checkUpdates = fork();
	if(checkUpdates == 0){
	  char *checkUpd_arglist[8];
	  checkUpd_arglist[0] = "/usr/sbin/softwareupdate";
	  checkUpd_arglist[1] = "-l";
	  checkUpd_arglist[2] = "|";
	  checkUpd_arglist[3] = "/usr/bin/tee";
	  checkUpd_arglist[4] = "-a";
	  checkUpd_arglist[5] = home;
	  checkUpd_arglist[6] = "&>/dev/null";
	  checkUpd_arglist[7] = NULL;
	  // Print the output of the command generated above to file rather than stdout:
	  int bak, new;
	  fflush(stdout);
	  bak = dup(1);
	  new = open(home, O_WRONLY);
	  dup2(new, 1);
	  close(new);
	  /* your code here ... */
	  execvp(checkUpd_arglist[0], checkUpd_arglist);
	  fflush(stdout);
	  dup2(bak, 1);
	  close(bak);
	}
	else if(checkUpdates >= 1){
	  setprogname("softwareupdate -l");
	  printf("\033]0;Checking for updates for macOS by running /usr/sbin/softwareupdate -l\007");
	  fprintf(stdout, "Checking for updates for macOS by running /usr/sbin/softwareupdate -l…\n");
	  waitpid(checkUpdates, &status, 0);
	  if(WIFEXITED(status)){
	    if(WEXITSTATUS(status) != 0)
	      return status;
	  }
	}
	else{
	  fprintf(stderr, "Failed to create the softwareupdate(8) process.\n");
	  exit(-1);
	}
	if(Search_in_File(home, "Software Update found the following new or updated software:") == 0){
	  printf("There is new or updated software available.\n");
	  if(Search_in_File(home, "[restart]") == 0){
	    printf("\033[01;31m***One or more software update(s) require(s) a system reboot. Please reboot the system once %s is complete***\033[00m\n", prog_name);
	    rb = 1;
	    sleep(5);
	  }
	  int installUpdates = fork();
	  if(installUpdates == 0){
	    char *installUpdates_arglist[3];
	    installUpdates_arglist[0] = "/usr/sbin/softwareupdate";
	    installUpdates_arglist[1] = "-ia";
	    installUpdates_arglist[2] = NULL;
	    execvp(installUpdates_arglist[0], installUpdates_arglist);
	  }
	  else if(installUpdates >= 1){
	    setprogname("softwareupdate -ia");
	    printf("\033]0;Installing updates for macOS by running /usr/sbin/softwareupdate -ia\007");
	    fprintf(stdout, "Installing updates for macOS by running /usr/sbin/softwareupdate -ia…\n");
	    waitpid(installUpdates, &status, 0);
	    if(WIFEXITED(status)){
	      if(WEXITSTATUS(status) != 0)
		return status;
	    }
	  }
	  else{
	    fprintf(stderr, "Could not create softwareupdate(8) process.\n");
	    exit(-1);
	  }
	}
	else{
	  printf("There is no new software available.\n");
	}
	printf("\033]0;Done running softwareupdate\007");
	removeFile(home);
      }
      else if(strncmp("n", ans_baseSystem, 1) == 0 || strncmp("N", ans_baseSystem, 1) == 0){
	return 0;
      }
      else{
	printf("Please type 'y' for 'yes' or type 'n' for 'no'.\n");
	updateBaseSystem();
      }
    }
    else{ // assume softwareupdate to be run every time
      printf("Run softwareupdate(8).\n");
      FILE* softUpd;
      char *line = NULL;
      size_t len = 0;
      ssize_t read;
      char *home = getenv("HOME");
      strcat(home, "/.softUpd.txt");
      softUpd = fopen(home,"w");
      fclose(softUpd);
      system("softwareupdate -l &");
      int checkUpdates = fork();
      if(checkUpdates == 0){
	char *checkUpd_arglist[8];
	checkUpd_arglist[0] = "/usr/sbin/softwareupdate";
	checkUpd_arglist[1] = "-l";
	checkUpd_arglist[2] = "|";
	checkUpd_arglist[3] = "/usr/bin/tee";
	checkUpd_arglist[4] = "-a";
	checkUpd_arglist[5] = home;
	checkUpd_arglist[6] = "&>/dev/null";
	checkUpd_arglist[7] = NULL;
	// Print the output of the command generated above to file rather than stdout:
	int bak, new;
	fflush(stdout);
	bak = dup(1);
	new = open(home, O_WRONLY);
	dup2(new, 1);
	close(new);

	execvp(checkUpd_arglist[0], checkUpd_arglist);
	fflush(stdout);
	dup2(bak, 1);FILE* softUpd;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *home = getenv("HOME");
	strcat(home, "/.softUpd.txt");
	softUpd = fopen(home,"w");
	fclose(softUpd);
	system("softwareupdate -l &");
	int checkUpdates = fork();
	if(checkUpdates == 0){
	  char *checkUpd_arglist[8];
	  checkUpd_arglist[0] = "/usr/sbin/softwareupdate";
	  checkUpd_arglist[1] = "-l";
	  checkUpd_arglist[2] = "|";
	  checkUpd_arglist[3] = "/usr/bin/tee";
	  checkUpd_arglist[4] = "-a";
	  checkUpd_arglist[5] = home;
	  checkUpd_arglist[6] = "&>/dev/null";
	  checkUpd_arglist[7] = NULL;
	  // Print the output of the command generated above to file rather than stdout:                                
	  int bak, new;
	  fflush(stdout);
	  bak = dup(1);
	  new = open(home, O_WRONLY);
	  dup2(new, 1);
	  close(new);
	  
	  execvp(checkUpd_arglist[0], checkUpd_arglist);
	  fflush(stdout);
	  dup2(bak, 1);
	  close(bak);
	}
	else if(checkUpdates >= 1){
	  setprogname("softwareupdate -l");
	  printf("\033]0;Checking for updates for macOS by running /usr/sbin/softwareupdate -l\007");
	  fprintf(stdout, "Checking for updates for macOS by running /usr/sbin/softwareupdate -l…\n");
	  waitpid(checkUpdates, &status, 0);
	  if(WIFEXITED(status)){
	    if(WEXITSTATUS(status) != 0)
	      return status;
	  }
	}
	else{
	  fprintf(stderr, "Failed to create the softwareupdate(8) process.\n");
	  exit(-1);
	}
	if(Search_in_File(home, "Software Update found the following new or updated software:") == 0){
	  printf("There is new or updated software available.\n");
	  if(Search_in_File(home, "[restart]") == 0){
	    printf("\033[01;31m***One or more software update(s) require(s) a system reboot. Please reboot the system once %s is complete***\033[00m\n", prog_name);
	    rb	= 1;
	    sleep(5);
	  }
	  int installUpdates = fork();
	  if(installUpdates == 0){
	    if(verbose == 1){
	      char *installUpdates_arglist[3];
	      installUpdates_arglist[0] = "/usr/sbin/softwareupdate";
	      installUpdates_arglist[1] = "-iav";
	      installUpdates_arglist[2] = NULL;
	      execvp(installUpdates_arglist[0], installUpdates_arglist);
	    }
	    else{
	      char *installUpdates_arglist[3];
	      installUpdates_arglist[0] = "/usr/sbin/softwareupdate";
	      installUpdates_arglist[1] = "-ia";
	      installUpdates_arglist[2] = NULL;
	      execvp(installUpdates_arglist[0], installUpdates_arglist);
	    }
	  }
	  else if(installUpdates >= 1){
	    setprogname("softwareupdate -ia");
	    if(verbose == 1) {
		printf("\033]0;Installing updates for macOS by running /usr/sbin/softwareupdate -iav\007");
		fprintf(stdout, "Installing updates for macOS by running /usr/sbin/softwareupdate -iav…\n");
	    }
	    else {
		printf("\033]0;Installing updates for macOS by running /usr/sbin/softwareupdate -ia\007");
	 	fprintf(stdout, "Installing updates for macOS by running /usr/sbin/softwareupdate -ia…\n");
	    }
	    waitpid(installUpdates, &status, 0);
	    if(WIFEXITED(status)){
	      if(WEXITSTATUS(status) != 0)
		return status;
	    }
	  }
	  else{
	    fprintf(stderr, "Could not create softwareupdate(8) process.\n");
	    exit(-1);
	  }
	}
	else{
	  printf("There is no new software available.\n");
	}
	removeFile(home);
      }
    }
  }
  else if(strcmp(getOS(), "FreeBSD") == 0)
  {
    struct utsname unameData;
    if(uname(&unameData) != 0)
    {
      fprintf(stderr, "An error has occurred when using the uname() function.\n");
      exit(1);
    }
    char *version = unameData.version;
    char *rel = unameData.release;
    char find = '.';
    const char *fbsdptr = strchr(version, find); // fbsd = FreeBSD.
    if(fbsdptr)
    {
      int i = fbsdptr - version;
      version[i] = '\0';
    }
    fprintf(stdout, "FreeBSD version: %s\n", rel);
    size_t n = 5;
    /*
      Fjerner de N første tegnene fra arrayen "rel", slik at vi bare står igjen med HEAD, RELEASE, 
      RCn eller ALPHAn, der n er alfa-, beta- eller release candidate-nummeret, f.eks. RC3 eller ALPHA1:
     */
    memmove(rel,rel+n, strlen(rel)-n+1);
    if(strstr(rel, "RELEASE") != NULL) {
      return askUpdateFreeBSD();
    }
    else if(strstr(rel, "BETA") != NULL) {
      return askUpdateFreeBSD();
    }
    else if(strstr(rel, "RC") != NULL) {
      return askUpdateFreeBSD();
    }
  }
  //sys_home = NULL;
  char find = '.';
  const char *ptr = strchr(sys_home, find);
  if(ptr) 
  {
    int index = ptr - sys_home;
    sys_home[index] = '\0';
  }
  printf("\033]0;\007");
  #else
  updateLinux();
  #endif
  return 0;
}

#ifndef __linux__
int askUpdateFreeBSD()
{
  int res = 0;
  printf("Would you like to use freebsd-update(8) to update the base system?(Y/n) ");
  char *ans_baseSystem;
  size_t ans_baseSystem_linecap = 0;
  ans_baseSystem = (char *)malloc(ans_baseSystem_linecap +1);
  if(getline(&ans_baseSystem, &ans_baseSystem_linecap, stdin) == -1){
    fprintf(stderr, "End-of-file reached or something else has gone wrong.\n");
    exit(-1);
  }
  char *tmp = strstr(ans_baseSystem, "\t");
  while((tmp = strstr(ans_baseSystem, "\n")) != NULL){
    long len = strlen(ans_baseSystem);
    memmove(tmp, tmp +1, len);
  }
  long ansUPDATINGfile_length = strlen(ans_baseSystem);
  if(ansUPDATINGfile_length > 0){
    removeWhitespaceFromAnswer();
  }
  if(strncmp("y", ans_baseSystem, 1) == 0 || strncmp("Y", ans_baseSystem, 1) == 0 || strncmp("", ans_baseSystem, 1) == 0)
  {
    setenv("PAGER", "more -e", 1);
    FILE* FreeBSDupdate;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *fhome = ".FreeBSD.txt"; //getenv("HOME");
    //strcat(fhome, "/.FreeBSD.txt");
    FreeBSDupdate = fopen(fhome,"w");
    fclose(FreeBSDupdate);
    char cmd[150] = "freebsd-update fetch install --not-running-from-cron | tee -a ";
    strcat(cmd, fhome);
    printf("\033]0;Updating FreeBSD base system by running /usr/sbin/freebsd-update fetch install\007");
    fprintf(stdout, "Updating FreeBSD base system by running /usr/sbin/freebsd-update fetch install…\n");
    res = system(cmd);
    // Print the output of the command generated above to file rather than stdout:
    int bak, new;
    fflush(stdout);
    bak = dup(1);
    new = open(fhome, O_WRONLY);
    dup2(new, 1);
    close(new);
    
    fflush(stdout);
    dup2(bak, 1);
    close(bak);
    if(Search_in_File(fhome, "/boot/kernel/kernel") == 0){
      fprintf(stdout, "****Kernel has been updated. To use the new kernel, please reboot your system.***\n");
      rb = 1;
      sleep(5);
    }
    removeFile(fhome);
  }
  else if(strncmp("n", ans_baseSystem, 1) == 0 || strncmp("N", ans_baseSystem, 1) == 0) {
    return 0;
  }
  else {
    printf("Please type y for yes or type n for no.\n");
    askUpdateFreeBSD();
  }
  return res;
}
#endif

void updateSunOS()
{
  int status = 0;
  fprintf(stdout, "Running pkg install pkg:/package/pkg on SunOS\n");
  int pkg1 = fork();
  if(pkg1 == 0)
  {
    char *pkg1_arglist[4];
    pkg1_arglist[0] = "/usr/bin/pkg";
    pkg1_arglist[1] = "install";
    pkg1_arglist[2] = "pkg:/package/pkg";
    pkg1_arglist[3] = NULL;
    execvp(pkg1_arglist[0], pkg1_arglist);
  }
  else if(pkg1 >= 1)
  {
    waitpid(pkg1, NULL, 0);
    if(WIFEXITED(status))
    {
      if(WEXITSTATUS(status) != 0)
      {
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
    }
  }
  else
  {
    fprintf(stderr, "Failed to create pkg process.\n");
    exit(-1);
  }
  fprintf(stdout, "Running pkg install pkg update --accept on SunOS\n");
  int pkg2 = fork();
  if(pkg2 == 0)
  {
    char *pkg2_arglist[4];
    pkg2_arglist[0] = "/usr/bin/pkg";
    pkg2_arglist[1] = "update";
    pkg2_arglist[2] = "--accept";
    pkg2_arglist[3] = NULL;
    execvp(pkg2_arglist[0], pkg2_arglist);
  }
  else if(pkg2 >= 1)
  {
    waitpid(pkg2, NULL, 0);
    if(WIFEXITED(status))
    {
      if(WEXITSTATUS(status) != 0)
      {
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
    }
  }
  else
  {
    fprintf(stderr, "Failed to create pkg process.\n");
    exit(-1);
  }
}

void removeWhitespaceFromAnswer(char *ans)
{
  // Fjerner mellomrom fra tekststrengen.
    char *str;
    str=ans;
    while(*str == ' ')
      str++;
    if(str != ans)
      memmove(ans, str, strlen(str)+1);
}

void updateLinuxZypper()
{
  int status, res, err;
  int zypperref = fork();
  if(zypperref == 0){
    char *zypperref_arglist[3];
    zypperref_arglist[0] = "/usr/bin/zypper";
    zypperref_arglist[1] = "ref";
    zypperref_arglist[2] = NULL;
    res = execvp(zypperref_arglist[0], zypperref_arglist);
    if(res != 0)
      exitApp(res);
  }
  else if(zypperref >= 1){
    waitpid(zypperref, NULL, 0);
    if(WIFEXITED(status)){
      if(WEXITSTATUS(status) != 0){
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
    }
  }
  else{
    fprintf(stderr, "Failed to create zypper process.\n");
    printf("\033]0;\007");
    exit(-1);
  }
  int zypperdup = fork();
  if(zypperdup == 0){
    char *zypper_dup_arglist[3];
    zypper_dup_arglist[0] = "/usr/bin/zypper";
    zypper_dup_arglist[1] = "dup";
    zypper_dup_arglist[2] = NULL;
    res = execvp(zypper_dup_arglist[0], zypper_dup_arglist);
    if(res != 0){
      exitApp(res);
    }
  }
  else if(zypperdup >= 1)
  {
    waitpid(zypperdup, NULL, 0);
    if(WIFEXITED(status)){
      if(WEXITSTATUS(status) != 0){
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
    }
  }
  else
  {
    fprintf(stderr, "Failed to create zypper process.\n");
    printf("\033]0;\007");
    exit(-1);
  }
  int zypper = fork();
  if(zypper == 0){
    char *zypper_update_arglist[3];
    zypper_update_arglist[0] = "/usr/bin/zypper";
    zypper_update_arglist[1] = "update";
    zypper_update_arglist[2] = NULL;
    res = execvp(zypper_update_arglist[0], zypper_update_arglist);
    if(res != 0){
      exitApp(res);
    }
  }
  else if(zypper >= 1)
  {
    waitpid(zypper, NULL, 0);
    if(WIFEXITED(status)){
      if(WEXITSTATUS(status) != 0){
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
    }
  }
  else
  {
    fprintf(stderr, "Failed to create zypper process.\n");
    printf("\033]0;\007");
    exit(-1);
  }
}

void updateLinux()
{
  // This assumes that the user uses apt-get.
  int status = 0;
  printf("\033]0;Updating package information by running /usr/bin/apt update\007");
  printf("Updating package information by running /usr/bin/apt update\n");
  int aptupdate = fork();
  if(aptupdate == 0)
  {
    char *apt_update_arglist[3];
    apt_update_arglist[0] = "/usr/bin/apt";
    apt_update_arglist[1] = "update";
    apt_update_arglist[2] = NULL;
    int res = execvp(apt_update_arglist[0], apt_update_arglist);
    int err = errno;
    if(err == 2){ // errno 2 betyr at fila eller mappa ikke finnes.
      updateLinuxZypper();
      return;
    }	
  }
  else if(aptupdate >= 1)
  {
    waitpid(aptupdate, NULL, 0);
    if(WIFEXITED(status)){
      if(WEXITSTATUS(status) != 0){
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
      else{
	printf("\033]0;\007");
	printf("\n");
      }
    }
  }
  else
  {
    fprintf(stderr, "Failed to create apt process.\n");
    printf("\033]0;\007");
    exit(-1);
  }
  printf("\033]0;Fetching new software by running /usr/bin/apt dist-upgrade\007");
  printf("Fetching new software by running /usr/bin/apt dist-upgrade\n");
  int aptdistupgrade = fork();
  if(aptdistupgrade == 0)
  {
    char *apt_distupgrade_arglist[3];
    apt_distupgrade_arglist[0] = "/usr/bin/apt";
    apt_distupgrade_arglist[1] = "dist-upgrade";
    apt_distupgrade_arglist[2] = NULL;
    execvp(apt_distupgrade_arglist[0], apt_distupgrade_arglist);
  }
  else if(aptdistupgrade >= 1)
  {
    waitpid(aptdistupgrade, NULL, 0);
    if(WIFEXITED(status)){
      if(WEXITSTATUS(status) != 0){
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
      else{
	printf("\033]0;\007");
	printf("\n");
      }
    }
  }
  else
  {
    fprintf(stderr, "Failed to create apt process.\n");
    printf("\033]0;\007");
    exit(-1);
  }
  printf("\033]0;Removing old and unused software using /usr/bin/apt autoremove -y\007");
  printf("Removing old and unused softare by running /usr/bin/apt autoremove -y\n");
  int aptautoremove = fork();
  if(aptautoremove == 0){
    char *aptautorm[4];
    aptautorm[0] = "/usr/bin/apt";
    aptautorm[1] = "autoremove";
    aptautorm[2] = "-y";
    aptautorm[3] = NULL;
    execvp(aptautorm[0], aptautorm);
  }
  else if(aptautoremove >=1){
    waitpid(aptautoremove, NULL, 0);
    if(WIFEXITED(status)){
      if(WEXITSTATUS(status) != 0){
	fprintf(stderr, "Something has gone wrong and updateports will quit. Exit status: %d\n", status);
	printf("\033]0;\007");
	exit(status);
      }
    }
  }
  else{
    fprintf(stderr, "Failed to create apt process.\n");
    printf("\033]0;\007");
    exit(-1);
  }
  printf("\033]0;\007");
}

/*
* Oppdateringsprosessen her foreger ved at /usr/ports/infrastructures/bin/out-of-date kjxres.
* Dersom dette programmet finner utdaterte porter, oppdateres disse.
* (vet ikke helt hvordan akkurat ne.)
*/
void updateOpenBSD()
{
  fprintf(stdout, "%s expects that the user is following the current branch. If not, things might go wrong.\n", prog_name);
  sleep(5);
  chdir("/usr/ports");
  int status_cvs, proc = fork();
  if(proc == 0){
    fprintf(stdout, "Updating ports via CVS...\n");
    char *cvs[4];
    cvs[0] = "cvs";
    cvs[1] = "up";
    //cvs[2] = "-r";
    //cvs[3] = "TAG";
    cvs[2] = "-Pd";
    cvs[3] = NULL;
    execvp(cvs[0], cvs);
  }
  else if(proc >= 0){
    #ifndef __linux__
    setprogname("cvs update");
    #endif
    waitpid(proc, &status_cvs, 0);
    if(WIFEXITED(status_cvs)){
      if(WEXITSTATUS(status_cvs) != 0){
	fprintf(stderr, "There is a problem updating the port system. The returned status code was %d.\n", WEXITSTATUS(status_cvs));
	exitApp(WEXITSTATUS(status_cvs));
      }
    }
  }
  else{
    fprintf(stderr, "Could not create a CVS process.\n");
  }

  //ofd = out-of-date
  int status_ofd, proc_ofd = fork();
  if(proc_ofd == 0){
    fprintf(stdout, "Running /usr/ports/infrastructures/bin/out-of-date...\n");
    char *ofd[3];
    ofd[0] = "/usr/ports/infrastructure/bin/out-of-date";
    ofd[1] = "-x";
    ofd[2] = NULL;
    execvp(ofd[0], ofd);
  }
  else if(proc_ofd >= 0){
    #ifndef __linux__
    setprogname("out-of-date");
    #endif
    if(WIFEXITED(status_ofd)){
      if(WEXITSTATUS(status_ofd) != 0){
	fprintf(stderr, "There is a problem running the out-of-date script. The returned status code was %d.\n", WEXITSTATUS(status_ofd));
	exitApp(WEXITSTATUS(status_ofd));
      }
    }
  }
}

void checkConnection(char *hostname, int runs) {
  struct hostent *hostinfo = gethostbyname(hostname);
  if (hostinfo == NULL){
    runs++;
    if(runs == 1) checkConnection("www.google.com", runs);
    if(runs == 2) checkConnection("www.facebook.com", runs);
    if(runs == 3) checkConnection("www.twitter.com", runs);
    if(runs > 3) {
      fprintf(stdout, "%s requires an active internet connection.\n", prog_name);
      exitApp(100);
    }
  }
  else {
    fprintf(stdout, "connection OK\n");
  }
}

int main(int argc, char ** argv)
{
//currentcmd = "updateports";
  prog_name = "updateports";
  portmaster_arg = 0;
  portupgrade_arg = 0;
  appToRun = "null";
  signal(SIGTSTP, ctrl_z);
  signal(SIGCONT, sigCont);
  signal(SIGINT, ctrl_c);
  signal(SIGSEGV, segFault);
  signal(SIGBUS, sigBus);
  #ifdef SIGINFO
  signal(SIGINFO, sigInfo);
  #endif
  fprintf(stdout, "Checking internet connection… ");
  checkConnection("ftp://ftp.freebsd.org", 0);
  fprintf(stdout, "Checking operating system... ");
  printf("%s\n", getOS());
  int opt;
  if(strcmp(getOS(), "NetBSD") == 0){
    if(argc > 1){
      fprintf(stderr, "%s (NetBSD): usage %s\n", prog_name, prog_name);
      return 1;
    }
    else{
      syslog(LOG_NOTICE, "Running updateports on NetBSD.\n");
      updatePkgsrc();
      return 0;
    }
  }
  else if(strcmp(getOS(), "OpenBSD") == 0){
    if(argc > 1){
      fprintf(stderr, "%s (OpenBSD): usage %s\n", prog_name, prog_name);
      return 1;
    }
    else{
      syslog(LOG_NOTICE, "Running updateports on OpenBSD.\n");
      updateOpenBSD();
      return 0;
    }
  }
  else if(strcmp(getOS(), "Linux") == 0)
  {
    syslog(LOG_NOTICE, "Running updateports on Linux.\n");
    if(argc > 1)
    {
      fprintf(stderr, "On Linux, updateports does not accept any options or parameters.\n");
      return 1;
    }
    else
    {
      updateBaseSystem();
    }
  }
  else if(strcmp(getOS(), "SunOS") == 0){
    syslog(LOG_NOTICE, "Running updateports on SunOS (Solaris).\n");
    if(argc > 1){
      fprintf(stderr, "The Solaris version of %s does not accept parameters.\n", prog_name);
      return 1;
    }
    else{
      updateSunOS();
    }
  }
  else if(strcmp(getOS(), "FreeBSD") == 0)
  {  
    syslog(LOG_NOTICE, "Running updateports on FreeBSD.\n");
    
    if(argc == 1){
      if(checkExec("/usr/sbin/pkg")){
	appToRun = "/usr/sbin/pkg";
      }
    }
    else{
      int i = 0;
      while(i < argc){
	if(i == 0){
	  i++;
	  continue;
	}
	else{
	  if(strncmp(argv[i], "-", 1) != 0){
	    fprintf(stderr, "%s usage (FreeBSD):\n\%s\n\%s -p[-i]\n%s -p", prog_name, prog_name, prog_name, prog_name);
	    exitApp(1);
	  }
	}
	i++;
      }
      while((opt = getopt(argc, argv, "ipPv")) != -1){
	switch(opt){
	case 'p':
	  if(checkExec("/usr/local/sbin/portmaster")){
	    appToRun = "/usr/local/sbin/portmaster";
	    portmaster_arg = 1;  
	  }
	  else{
	    fprintf(stderr, "The portmaster utility does not seem to be installed.\n");
	    syslog(LOG_ERR, "The portmaster utility does not seem to be installed.\n");
	    return 1;
	  }
	  break;
	case 'P':
	  if(checkExec("/usr/local/sbin/portupgrade")){
	    portupgrade_arg = 1;
	    appToRun = "/usr/local/sbin/portupgrade";
	  }
	  else{
	    fprintf(stderr, "The portupgrade utility does not seem to be installed.\n");
	    syslog(LOG_ERR, "The portupgrade utility does not seem to be installed.\n");
	    return 1;
	  }
	  break;
	case 'v':
	  if(portupgrade_arg){
	    verbose=1;
	  }
	  else{
	    fprintf(stderr, "On FreeBSD, the -v flag can only be used with the Portupgrade (-P) utility. Syntax: %s -Pv or %s -P -v.\n", prog_name, prog_name);
	    exitApp(1);
	  }
	case 'i':
	  /*if(strcmp(appToRun, "null") == 0){
	    fprintf(stderr, "The -i flag can only be used with the Portmaster or Portupgrade utility.\n");
	    exitApp(2);
	  }
	  else*/
	    interactive =1;
	  break;
	case '?':
	  fprintf(stderr, "%s usage (FreeBSD):\n%s\n%s -p[-i]\n%s -P[-i -v]\n",prog_name, prog_name, prog_name, prog_name);
	  exitApp(1);
	  break;
	}
      }
    }
    if(interactive && strcmp(appToRun, "null") == 0){
      fprintf(stderr, "The -i flag can only be used with the Portmaster or Portupgrade utility.\n");
      exitApp(2);
    }
    int retVal = updateFreeBSD();
    if(retVal != 0)
    {
      fprintf(stderr, "Something has gone wrong and the updating process has been stopped.\n");
      syslog(LOG_ERR, "Something has gone wrong and the updating process has been stopped.\n");
      exitApp(retVal);
      //return retVal;
    }
    syslog(LOG_NOTICE, "Done running updateports on FreeBSD.\n");
  }
  else if(strcmp(getOS(), "Darwin") == 0)
  {
    syslog(LOG_NOTICE, "Running updateports on Darwin.\n");
    while((opt = getopt(argc, argv, ":yv")) != -1){
      switch(opt){
      case 'y':
	softupdate = 1;
	break;
      case 'v':
	verbose = 1;
	break;
      case '?':
	fprintf(stderr, "On Darwin, updateports can only be run with -y and -v options.\n");
	return 1;
      }
    }
    updateBaseSystem();
    int retVal = updateDarwin();
    if(retVal != 0)
    {
      fprintf(stderr, "Something has gone wrong and the updating process has been stopped.\n");
      exitApp(retVal);
      //return retVal;
    }
    else{
      printf("Done.\n");
      syslog(LOG_NOTICE, "updateports is now complete.\n");
    }
    /*if(argc == 2)
    {
      if(strcmp(argv[1], "-y") == 0)
      {
	softupdate = 1;
      }
      else if(strcmp(argv[1], "-v") == 0)
      {
	verbose = 1;	
      }
      else if(strcmp(argv[1], "-pm") == 0)
	{
	  fprintf(stderr, "Only users of FreeBSD can use the -pm option.\n");
	  return 1;
	}
      else if(strcmp(argv[1], "-pu") == 0)
	{
	  fprintf(stderr, "Only users of FreeBSD can use the -pu option.\n");
	  return 1;
	}
      else
      {
	fprintf(stderr, "You typed an illegal option.\n");
	return 1;
      }
      updateBaseSystem();
      int retVal = updateDarwin();
      if(retVal != 0)
	{
	  fprintf(stderr, "Something has gone wrong and the updating process has been stopped.\n");
	  return retVal;
	}
      else
	printf("Done.\n");
    }
    else if(argc == 3)
    {
      if(strcmp(argv[2], "-v") == 0)
      {
	verbose = 1;
      }
      else if(strcmp(argv[2], "-y") == 0)
      {
	softupdate = 1;
      }
      else
      {
	fprintf(stderr, "You typed an illegal option.\n");
	return 1;
      }
      int retVal = updateDarwin();
      if(retVal != 0)
	{
	  fprintf(stderr, "Something has gone wrong and the updating process has been stopped.\n");
	  return retVal;
	}
      else
      {
	printf("Done.\n");
        syslog(LOG_NOTICE, "updateports is now complete.\n");
      }
    }
    else
    {
      updateBaseSystem();
      int retVal = updateDarwin();
      if(retVal != 0)
	{
	  fprintf(stderr, "Something has gone wrong and the updating process has been stopped.\n");
	  return retVal;
	}
      else
      {
	printf("Done.\n");
	syslog(LOG_NOTICE, "updateports is now complete.\n");
      }
    }*/
  }
  return 0;
}
