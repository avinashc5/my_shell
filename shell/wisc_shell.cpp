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

		char* pch = strtok(line_c, ";");
		std::vector<char*> commands;
		while (pch != NULL){
			commands.push_back(pch);
			pch = strtok(NULL, ";");
		}

		std::vector<std::vector<char*>> command_args(commands.size(), std::vector<char*>());
		for (int i = 0; i < commands.size(); i++){
			pch = strtok(commands[i], " ");
			while (pch != NULL){
				command_args[i].push_back(pch);
				if (pch[0] == 'q' && pch[1] == 'u' && pch[2] == 'i' && pch[3] == 't'){
					RUN = false;
				}
				pch = strtok(NULL, " ");
			}
			command_args[i].push_back(NULL);
		}

		if (!RUN) break;

		for (int i = 0; i < command_args.size(); i++){
			pid_t c_pid = fork();
			if (c_pid == -1){
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (c_pid > 0){ // Parent process
				int status;
				waitpid(c_pid, &status, 0);
			}
			else if (c_pid == 0){ // Child process
				int status_code = execvp(command_args[i][0], command_args[i].data());
				if (status_code == -1){
					perror("Error");
					exit(EXIT_FAILURE);
				}

				exit(EXIT_SUCCESS);
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
grep
echo
quit
*/