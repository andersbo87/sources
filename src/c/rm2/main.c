#include <stdio.h>
#include <removefile.h>
int removefile_status_callback(removefile_state_t state, const char * path)//, void * context) 
{
	fprintf(stderr, "File deleted: %s", path);
	return REMOVEFILE_PROCEED;
}
int err;
int main (int argc, const char * argv[]) {
    /* Initialize a state variable */
	removefile_state_t s;
	s = removefile_state_alloc();
	int *removefile_confirm_callback;
	/* Set callback function properties */
	removefile_state_set(s, REMOVEFILE_STATE_CONFIRM_CALLBACK, removefile_confirm_callback);
	removefile_state_set(s, REMOVEFILE_STATE_CONFIRM_CONTEXT, NULL);
	/* Recursively remove all files and directories while keeping parent tmp directory,
	 calling a confirm callback prior to each file deletion. */
	removefile("Doc2", s, REMOVEFILE_RECURSIVE);// | REMOVEFILE_KEEP_PARENT);
	/* Release the state variable. */
	removefile_state_free(s);
	
}
