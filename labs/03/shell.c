#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int cd(char **args);
int help(char **args);
int my_exit(char **args);

char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[]) (char **) = {&cd, &help,&my_exit};


char *read_line(void){
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return line;
}

char **split_line(char *line){
 	char *token;
 	char **tokens = malloc(64 * sizeof(char*));
 	int pos = 0;

	if (!tokens) {
		fprintf(stderr, "error\n");
	    exit(EXIT_FAILURE);
	}

  	token = strtok (line, " \t\r\n\a");
  	while (token != NULL)
  	{
    	tokens[pos] = token;
    	pos++;
    	token = strtok (NULL,  "\t\r\n\a");
  	}
  	tokens[pos] = NULL;
  	return tokens;
}

int launch_process(char **args){
	pid_t pid;
	pid_t wpid;
	int status;

	pid = fork();

  	if (pid == 0) {
    	if (execvp(args[0], args) == -1) {
      	fprintf(stderr, "Error forking, errno = %d\n", errno);
    	}
    	exit(-1);
    }
	else if(pid < 0){
		fprintf(stderr, "Error forking, errno = %d\n", errno);
		return 1;
	}
	else{
		do{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}


int builtins_number() {
  return sizeof(builtin_str) / sizeof(char *);
}

int cd(char **args){
	if (args[1] == NULL) {
    	fprintf(stderr, "Error, errno = %d\n", errno);
    }
	return 1;
}

int help(char **args)
{
  int i;

  printf("Built in commands:\n");

  for (i = 0; i < builtins_number(); i++) {
    printf(" *%s\n", builtin_str[i]);
  }
  return 1;
}

int my_exit(char **args){
	return 0;
}

int execute_commands(char **args){
	int i;

	if (args[0] == NULL){
		return 1;
	}

	for(i = 0; i < builtins_number(); i++){
		if(strcmp(args[0], builtin_str[i]) == 0){
			return (*builtin_func[i])(args);
		}
	}
	return launch_process(args);
}

int main(int argc, char **argv){
	
	char *line;
	char **args;
	int status;

	do{
		printf("¯\\_(ツ)_/¯ ");
		line = read_line();
		args = split_line(line);
		status = execute_commands(args);
	}
	while(status);


	return EXIT_SUCCESS;
}