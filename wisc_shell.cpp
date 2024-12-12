#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	bool RUN = true;
	std::string prompt = "prompt> ";
	while (RUN){
		std::cout << prompt;
		std::string line;
		getline(std::cin, line);
		char* line_c = new char[line.size() + 1];
		strcpy(line_c, line.c_str());
		char* pch = strtok(line_c, " ");
		std::vector<char*> command;
		while (pch != NULL){
			command.push_back(pch);
			if (pch[0] == 'q' && pch[1] == 'u' && pch[2] == 'i' && pch[3] == 't'){
				RUN = false;
			}
			pch = strtok(NULL, " ");
		}
		command.push_back(NULL);
		char* a_command[command.size()];
		for (int i = 0; i < command.size(); i++){
			a_command[i] = command[i];
		}
		if (!RUN) break;
		pid_t c_pid = fork();
		int status;
		if (c_pid == -1){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (c_pid > 0){ // Parent process
			waitpid(c_pid, &status, 0);
		}
		else { //Child Process
			int status_code = execvp(a_command[0], a_command);

			if (status_code == -1){
				perror("Error");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/*
Commands supported:
ls
pwd
mkdir
rm
rmdir
quit
*/