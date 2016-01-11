/*
 *	Colin Samplawski
 *	Sam Mergendahl
 *
 *	CS Logins:
 *	samplawski
 *	mergenda
 *
 *	Emails:
 *	csamplawski@wisc.edu
 *	smergendahl@wisc.edu
 *
 *	NetIDs
 *	csamplawski
 *	smergendahl
 *
 *	Program 2a
 *	CS537
 *	Fall 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>    
#include <ctype.h>

char error_message[30] = "An error has occurred\n";
char prompt[7] = "mysh # ";
char history[20][600];
int indices[20];
int command_count = 0;
int history_size = 0;
int batch_mode = 0;

// removing trailing and leading whitespace from a string
char * remove_whitespace(char * str) {
	char *end;
	
	// remove leading whitespace
	while(isspace(*str)) {
		str++;
	} 
	 
	// string was all whitespace
	if (*str == '\0') {
    	return str;
	}
	
	// start at the end of the string
	end = str + strlen(str) - 1;
	
	// remove trailing whitesapce
	while(end > str && isspace(*end)) {
		end--;
	}
	
	// add a new null terminate char
	*(end + 1) = '\0';
	
	return str;
}

// prints the error message
void print_error_msg() {
	write(STDERR_FILENO, error_message, strlen(error_message));
}

// prints the prompt, if not in batch mode
void print_prompt() {
	if (!batch_mode) {
		write(STDOUT_FILENO, prompt, strlen(prompt));
	}
}


// adds a command to history, removing the top element if history is full
void add_to_history(char* str, int num) {
	if (history_size == 20) {
		int i;
		for (i = 0; i < 19; i++) {
			strcpy(history[i], history[i + 1]);
			indices[i] = indices[i + 1];
		}
		strcpy(history[history_size - 1], str);
		indices[history_size - 1] = num;
	} else {
		strcpy(history[history_size], str);
		indices[history_size] = num;
		history_size++;
	}
}

// prints the history to output with command number
void print_history() {
	int i;
	for (i = 0; i < history_size; i++) {
		char num_str[16];
		sprintf(num_str, "%d ", indices[i]);
		write(STDOUT_FILENO, num_str, strlen(num_str));
		write(STDOUT_FILENO, history[i], strlen(history[i]));
	}
}

int main(int argc, char *argv[]) {
	FILE *infile;
	int outfile, fd_stdout;
	fd_stdout = dup(1);
	int redirect = 0;

	if (argc == 1) {
		infile = stdin;
	} else if (argc == 2) {
		infile = fopen(argv[1], "r");
		if (infile == NULL) {
			print_error_msg();
			exit(1);
		}
		batch_mode = 1;
	} else {
		print_error_msg();
		exit(1);
	}

	char buffer[515];
	char *input;
	input = buffer;
	print_prompt();

	// main loop of the program
	while (fgets(input, 515, infile)) {
		if (strlen(input) > 513) {
			if (batch_mode) {
				write(STDOUT_FILENO, input, 512);
				write(STDOUT_FILENO, "\n", strlen("\n"));
			}

			print_error_msg();
			print_prompt();
			continue;
		}

		if (batch_mode) {
			write(STDOUT_FILENO, input, strlen(input));
		}

		char* copy;
		copy = strdup(input);
		copy = remove_whitespace(copy);
		
		// empty command
		if (strcmp(copy, "") == 0) {
			print_prompt();
			continue;
		}

		// index into history using '!'
		if (copy[0] == '!') {
			int index;
			int found = 0;

			// case of just '!' without number after
			if (strlen(copy) == 1) {
				if (history_size != 0) {
					input = strdup(history[history_size - 1]);
				} else {
					print_error_msg();
					print_prompt();
					continue;
				}

			// case of !n
			} else {
				// remove the ! from the start of the string
				strncpy(copy, copy + 1, strlen(copy));
				copy = remove_whitespace(copy);

				// convert n from string to an int
				long val;
				char *temp;
				val = strtol(copy, &temp, 10);
				if (val < 0 || errno == ERANGE || temp[0] != '\0') {
					print_error_msg();
					print_prompt();
					continue;
				} else {
					index = (int) val;
				}
				
				// search for n in the indices
				int i;
				for (i = 0; i < history_size; i++){
					if (indices[i] == index) {
						input = strdup(history[i]);
						found = 1;
						break;
					}
				}

				if (!found) {
					print_error_msg();
					print_prompt();
					continue;
				}
			}
		}
		
		// output redirection
		copy = strdup(input);
		char* temp;
		if (strstr(copy, ">") != NULL) {
			if (strstr(copy, ">>") != NULL) {
				print_error_msg();
				print_prompt();
				continue;
			}
			char* tok;
			tok = strtok(copy, ">");
			tok = strtok(NULL, ">");
			temp = strdup(tok);


			tok = strtok(NULL, ">");
			if (tok != NULL) {
				print_error_msg();
				print_prompt();
				continue;
			}
			temp = remove_whitespace(temp);
			int too_many_args = 0;
			int i;
			for (i = 0; i < strlen(temp); i++) {
				if (isspace(temp[i])) {
					too_many_args = 1;
					break;
				}
			}
			
			if (too_many_args) {
				print_error_msg();
				print_prompt();
				continue;
			}


			outfile = open(temp, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
			if (outfile < 0) {
				print_error_msg();
				print_prompt();
				continue;
			} else {
				// divert stdout to the file
				fd_stdout = dup(1);
				dup2(outfile, 1);
				redirect = 1;
			}
		}
		
		// add the input to history
		command_count++;
		add_to_history(input, command_count);
		input = remove_whitespace(input);
		
		// remove the '> file.txt' from the command in the case of redirection
		// in order to be pass to execvp
		if (redirect) {
			char* tok;
			tok = strtok(input, ">");
			tok = strtok(NULL, ">");
			input = remove_whitespace(input);
		}

		// built in exit command
		if (strcmp(input, "exit") == 0) {
			dup2(fd_stdout, 1);
			exit(0);
		}
		
		// built in history command
		if (strcmp(input, "history") == 0) {
			print_history();
			dup2(fd_stdout, 1);
			print_prompt();		
			continue;
		}	

		// spilt into command and args for execvp
		char* args[1024];
		char* tok;
		tok = strtok(input, " \t\n\v\f\r");
		int count = 0;
		while (tok != NULL) {
			args[count] = tok;
			count++;
			tok = strtok(NULL, " \t\n\v\f\r");
		}
		args[count] = NULL;	
		
		// fork the running process
		pid_t child_process;
		child_process = fork();
		if (child_process < 0) {
			// fork error
			print_error_msg();
			dup2(fd_stdout, 1);
			exit(0);
		} else if (child_process == 0) {
			// if the child is running, call execvp
			if (execvp(args[0], args)) {
				// execvp error
				print_error_msg();
				dup2(fd_stdout, 1);
			}
			exit(0);
		} else {
			// if the parent is running, wait for the child
			waitpid(child_process, NULL, 0);
		}
		
		// restore output to stdout
		dup2(fd_stdout, 1);
		print_prompt();
	}
	return 0;
}
