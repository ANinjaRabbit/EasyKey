#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

void addKeybindLine(bool neovim, bool recursive, bool insertmode, bool normalmode, bool visualmode);

int main(int argc, char *argv[])
{
	string help = "Usage: vimek <vim-distro> [options]\nYou needn't arrange the parameters in order.\n\nOptions:\n    --n: Choose NeoVim\n    --v: Choose Vim\n    -v: Print version & copyright messages\n\n    -m: Non-recursive, like add a 'nore' before 'map'\n    -i: Make the key in INSERT MODE only\n    -n: Make the key in NORMAL MODE only\n    -l: Make the key in VISUAL MODE only";
	bool neovim;
	bool recursive = true;
	bool insertmode = false;
	bool normalmode = false;
	bool visualmode = false;
	if (argc <= 1||argc > 4)
	{
		cout << help << endl;
		exit(1);
	}
	else if (strcmp(argv[1], "-v") == 0)
	{
		cout << help << endl;
		exit(0);
	}
	bool has_used[3] = {false,false,false};
	for(int i = 1;i < argc;i++)
	{
	  if (strcmp(argv[i], "--n") == 0&& !has_used[0])
	    {
	      neovim = true;
	      has_used[0] = 1;
	    }
	  else if (strcmp(argv[i], "--v") == 0&&!has_used[0])
	    {
	      neovim = false;
	      has_used[0] = 1;
	    }
	  else if (strcmp(argv[i], "-m") == 0&&!has_used[1])
	    {
	      recursive = false;
	      has_used[1] = 1;
	    }
	  else if (strcmp(argv[i], "-i") == 0&&!has_used[2])
	    {
	      insertmode = true;
	      has_used[2] = 1;
	    }
	  else if (strcmp(argv[i], "-n") == 0 && !has_used[2])
	    {
	      normalmode = true;
	      has_used[2] = 1;
	    }
	  else if (strcmp(argv[i], "-l") == 0 && !has_used[2])
	    {
	      visualmode = true;
	      has_used[2] = 1;
	    }
	  else
	    {
	      cout<<"option error\n";
	      cout << help << endl;
	      exit(1);
	    }
	}
	if(!has_used[0])
	{
	      cout<<"option error\n";
	      cout << help << endl;
	      exit(1);
	}
	  
	addKeybindLine(neovim, recursive, insertmode, normalmode, visualmode);
	return 0;
}

void addKeybindLine(bool neovim, bool recursive, bool insertmode, bool normalmode, bool visualmode)
{
	string key;
	string cmd;
	string cfgpath;
	string sed;
	string merged;
	int whatMode; // 0 means all mode, 1 means insert, 2 means normal, 3 means visual
	
	if (insertmode == false && normalmode == false && visualmode == false)
	{
		whatMode = 0;
	}
	else if (insertmode == true && normalmode == false && visualmode == false)
	{
		whatMode = 1;
	}
	else if (insertmode == false && normalmode == true && visualmode == false)
	{
		whatMode = 2;
	}
	else if (insertmode == false && normalmode == false && visualmode == true)
	{
		whatMode = 3;
	}
	
	cout << "Please enter the key: ";
	cin >> key;
	cout << "Please enter the command: ";
	cin >> cmd;
	
	
	if (neovim == true)
	{
		cfgpath = "~/.config/nvim/init.vim";
	}
	else
	{
		cfgpath = "~/.vim/vimrc";
	}
	
	if (recursive == true && whatMode == 0)
	{
		merged = "map "+ key, " "+ cmd;
	}
	else if (recursive == false && whatMode == 0)
	{
		merged = "noremap ", key, " ", cmd;
	}
	else if (recursive == true && whatMode == 1)
	{
		merged = "imap ", key, " ", cmd;
	}
	else if (recursive == false && whatMode == 1)
	{
		merged = "inoremap ", key, " ", cmd;
	}
	else if (recursive == true && whatMode == 2)
	{
		merged = "nmap ", key, " ", cmd;
	}
	else if (recursive == false && whatMode == 2)
	{
		merged = "nnoremap ", key, " ", cmd;
	}
	else if (recursive == true && whatMode == 3)
	{
		merged = "vmap ", key, " ", cmd;
	}
	else if (recursive == false && whatMode == 3)
	{
		merged = "vnoremap", key, " ", cmd;
	}
	
	sed = "sed -i '$a\\"+merged+"' "+cfgpath;
	
	cout << sed << endl;
}
