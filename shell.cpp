#include <iostream>
#include <vector>
#include <sstream>
#include <queue>

enum executable{
	EXIT,
	LS,
	CD,
	MKDIR,
	INVALID
};

struct File {
	std::string file_name;

	File(std::string name){
		this->file_name = name;
	}
};

class Folder {
	std::string folder_name;
	std::vector<Folder*> folder_children;
	std::vector<File*> file_children;
	Folder* parent;

public:
	Folder(std::string name, Folder* par){
		this->folder_name = name;
		this->folder_children.clear();
		this->file_children.clear();
		this->parent = par;
	}

	void print_children(){
		std::cout << "Folders:" << std::endl;
		for (int i = 0; i < folder_children.size(); i++){
			std::cout << folder_children[i]->folder_name << std::endl;
		}
		std::cout << std::endl << "Files: " << std::endl;
		for (int i = 0; i < file_children.size(); i++){
			std::cout << file_children[i]->file_name << std::endl;
		}
		std::cout << std::endl;
	}

	Folder* find_folder_child(std::string folder_child_to_find){
		for (int i = 0; i < folder_children.size(); i++){
			if (folder_children[i]->folder_name == folder_child_to_find){
				return folder_children[i];
			}
		}
		return nullptr;
	}
};

class FileSystem {
	Folder* root;
	Folder* curr;
public:
	FileSystem(){
		root = new Folder("/", root);
		curr = root;
	}

	void ls(){
		curr->print_children();
	}

	void cd(std::string path){
		std::istringstream stream(path);
		std::queue<std::string> folders;
		std::string folder;
		while (getline(stream, folder, '/')){
			folders.push(folder);
		}
		if (folders.front() == ""){
			curr = root;
			folders.pop();
		}
		while (!folders.empty()){
			std::string folder_to_find = folders.front();
			folders.pop();
			Folder* child = curr->find_folder_child(folder_to_find);
			if (child == nullptr){
				std::cout << "Error: Invalid path. Folder " << folder_to_find << " does not exist" << std::endl;
				return;
			}
			curr = child;
		}
	}

	void mkdir(std::string folder_name){
		
	}
};

void to_be_done(){
	std::cout << "This is to be implemented" << std::endl;
}

int get_executable (const std::string command){
	if (command == "exit"){
		return executable::EXIT;
	}
	else if (command == "ls"){
		return executable::LS;
	}
	else if (command == "cd"){
		return executable::CD;
	}
	else if (command == "mkdir"){
		return executable::MKDIR;
	}
	else {
		return executable::INVALID;
	}
}

int main(){
	FileSystem file_system;
	std::string current_path = "> ";
	std::cout << current_path;
	std::string command;
	bool end = false;
	while (getline(std::cin, command)){
		std::vector<std::string> args;
		std::istringstream stream(command);
		std::string tmp;

		while (getline(stream, tmp, ' ')){
			args.push_back(tmp);
		}
		
		int comm = get_executable(args[0]);

		switch (comm){
			case executable::EXIT:
				std::cout << "Good Bye!" << std::endl;
				end = true;
				break;
			case executable::LS:
				file_system.ls();
				break;
			case executable::CD:
				if (args.size() == 1){
					file_system.cd("/");
				}
				else {
					file_system.cd(args[1]);
				}
				break;
			case executable::MKDIR:
				if (args.size() == 1 || args.size() > 2){
					std::cout << "Error: Invalid Name" << std::endl;
				}
				file_system.mkdir(args[1]);
				break;
			case executable::INVALID:
				std::cout << "Error: Invalid command" << std::endl;
				break;
		}

		if (end){
			break;
		}

		std::cout << current_path;
	}
}