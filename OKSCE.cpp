#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <windows.h>
#include <bits/stdc++.h>

#include <regex>

using namespace std;

enum support_lan
{
	NOT_SUPT,
	c,
	cpp,
	kt,
	L1_run,
	java,
	py
} lan;

static int fcheck();
static int customcmd();
static bool extention();
static void tip();
static void runapp();
static void autosave();
static void key_change();
static inline void beep();
static void outchange(bool);
static void check_options();
static inline void theme_call();
static inline void theme_change();
static void key_change_arg(string);

static bool run_stat, save_stat;
static int key = VK_F5, s, arg_count = 0, countz, tcount = countz = 0, customcmd_count = 0;
static char trigger_key[3] = "F5", colr[] = "color 04", colw[] = "color 0f", coly[] = "color 06", colb[] = "color 09", colg[] = "color 0a";
static char theme_temp, theme = '1', cmdline_args[256 * 2] = "", cmdrn[256 * 2] = "", ccmd[] = "gcc -o ", cpcmd[] = "g++ -o ", jcmd[] = "javac ", flname[40], outname[20], postfx[10], run[256 * 2];
static string customcmd_lines[10];
HWND hWnd = GetConsoleWindow();

static inline string convertToString(char *a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++)
	{
		s = s + a[i];
	}
	return s;
}

static void check_options()
{
	int a_size = sizeof(cmdline_args) / sizeof(char);
	string sub = convertToString(cmdline_args, a_size);
	string pat = "([^\\s](.)*?) -cus";
	string cusPat = ".+";
	string fkeyPat = "^-fkey [fF]([1-9]0?)$";
	smatch strmatch, fkeymatch;
	regex subr(pat);
	regex fkeyr(fkeyPat);

	int i = 0;
	while (regex_search(sub, strmatch, subr))
	{
		string temp = strmatch.str(1);
		if (regex_search(temp, fkeymatch, fkeyr))
		{
			key_change_arg(fkeymatch.str(1));
		}
		else
		{
			if (!i++)
			{
				if (arg_count)
				{
					strcat(run, strmatch.str(1).c_str());
					cout << "Arguments: " << strmatch.str(1) << endl;
				}
				else
				{
					strcat(cmdrn, temp.c_str());
					cout << "Added Command: " << temp << endl;
				}
			}
			else
			{
				customcmd_lines[customcmd_count++] = temp;
				cout << "Added Command: " << temp;
			}
			cout << endl;
		}
		// suffix to find the rest of the string.
		sub = strmatch.suffix().str();
	}
}

int main(int argc, char const *argv[])
{
	tip();
	lan = NOT_SUPT;
	if (argc == 1)
		goto FileName;
	else
	{
		strcpy(flname, argv[1]);
		if (argc > 2)
		{
			for (int i = 2; i < argc; i++)
			{
				strcat(cmdline_args, argv[i]);
				strcat(cmdline_args, " ");
			}
			strcat(cmdline_args, "-cus");
			if (!strcmp(flname, "-cus"))
			{
				check_options();
				cout << "\n\n~Press ESC for Settings\n~Press '" << trigger_key << "' to Auto Compile. . .\n\n #(Process Running). . .\n";
				goto back;
			}
			else
			{
				cout << "File Name: " << argv[1];
				arg_count = 2;
			}
		}
		cout << endl;
		goto check;
	}

FileName:
	tcount += countz;
	countz = s = arg_count = customcmd_count = 0;
	theme_call();
	cout << "\n\n\t\t**Auto compile and Execution**\t\t-$@n\n(Enter '-cus' for custom command)\nFile Name With Extention: ";
	fflush(stdin);
	cin.getline(flname, sizeof(flname));
	while (flname[s] != '\0' && flname[s] != ' ')
		s++;
	if (flname[s] == ' ')
	{
		flname[s++] = '\0';
		arg_count = 1;
	}
check:
	if (fcheck())
	{
		beep();
		goto FileName;
	}
	cout << "\n~Press ESC for Settings\n~Press '" << trigger_key << "' to Auto Compile. . .\n\n #(Process Running). . .\n";

back:
	if (GetAsyncKeyState(key))
	{
		if (save_stat)
			autosave();
		tcount++;
		system("cls");
		cout << "**Auto compile and Execution**  (" << ++countz << ")\n~Press '" << trigger_key << "' to Auto Compile...\n\n: " << cmdrn << endl;
		if (system(cmdrn))
		{
			BringWindowToTop(hWnd);
			beep();
		}
		else
		{
			system(colg);
			if (run_stat || customcmd_count)
				runapp();
		}
		cout << "\n(Process Running). . .\n";
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		cin.sync();
		system(coly);
		cout << "\n\n ~Press:\t|| (Total Compile: " << tcount << ")\n1. Change File Name\n2. Change Output Name\n3. Toggle Auto Execution ";
		if (run_stat)
			cout << "(AE: ON)";
		else
			cout << "(AE: OFF)";
		cout << "\n4. Toggle Auto Save ";
		if (save_stat)
			cout << "(AS: ON)";
		else
			cout << "(AS: OFF)";
		cout << "\n5. Launch New Compiler\n6. Change Theme\n7. Change Trigger Key\n~Press ESC to exit. . .\n";
		system("pause");
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			system("cls");
			theme_call();
			cout << flname << " || (Total Compile: " << tcount << ")\n";
			exit(0);
		}
		else if (GetAsyncKeyState(VK_NUMPAD1) || GetAsyncKeyState(0x31))
		{
			system("cls");
			argc = 1;
			goto FileName;
		}
		else if (GetAsyncKeyState(VK_NUMPAD2) || GetAsyncKeyState(0x32))
			outchange(true);
		else if (GetAsyncKeyState(VK_NUMPAD3) || GetAsyncKeyState(0x33))
		{
			if (customcmd_count)
				cout << "\nFeature Not Supported. . . \n";
			else
			{
				run_stat = !run_stat;
				cout << "\n #Auto Exc. Set#\n";
			}
		}
		else if (GetAsyncKeyState(VK_NUMPAD4) || GetAsyncKeyState(0x34))
		{
			save_stat = !save_stat;
			cout << "\n #Auto Save Set#\n";
		}
		else if (GetAsyncKeyState(VK_NUMPAD5) || GetAsyncKeyState(0x35))
		{
			system(colb);
			cout << "\n #Opening New Compiler#\n";
			char run[20] = "start ";
			strcat(run, argv[0]);
			system(run);
			system("pause");
		}
		else if (GetAsyncKeyState(VK_NUMPAD6) || GetAsyncKeyState(0x36))
		{
			theme_change();
		}
		else if (GetAsyncKeyState(VK_NUMPAD7) || GetAsyncKeyState(0x37))
		{
			key_change();
		}
		cin.sync();
		cout << "\n #(Process Running). . .\n";
	}
	sleep(1);
	theme_call();
	goto back;
}

static inline void beep()
{
	system(colr);
	Sleep(500);
}

static int fcheck()
{
	if (!strcmp(flname, "-cus"))
		return customcmd();

	DWORD fileAtt = GetFileAttributesA(flname);
	if (fileAtt == INVALID_FILE_ATTRIBUTES)
	{
		cout << "\n #File Not Found. . .";
		return 1;
	}
	else if (fileAtt & FILE_ATTRIBUTE_DIRECTORY)
	{
		cout << "\n #It is a Directory. . .";
		return 1;
	}

	int j, i = strlen(flname) - 1;
	while (flname[i] != '.')
		i--;
	strcpy(outname, flname);
	outname[i] = '\0';
	j = 0;
	while (flname[i] != '\0')
		postfx[j++] = tolower(flname[i++]);
	postfx[j] = '\0';
	if (extention())
	{
		cout << "\n #Sorry, Type Not Supported . . .\n Wish to add custom command line?.. (Y/N)? ";
		beep();
		char cuscmd = getch();
		if (cuscmd == 'y' || cuscmd == 'Y')
			return customcmd();
		return 1;
	}
	return 0;
}

static bool extention()
{
	// ADD LANGUAGE SUPPORT HERE
	if (!strcmp(postfx, ".c"))
		lan = c;
	else if (!strcmp(postfx, ".cpp"))
		lan = cpp;
	else if (!strcmp(postfx, ".java"))
		lan = java;
	else if (!strcmp(postfx, ".py"))
		lan = py;
	else if (!strcmp(postfx, ".kt"))
		lan = kt;
	else
		return true;
	// LANGUAGE SUPPORT END
	if (arg_count == 1)
	{
		int k;
		for (k = 0; flname[s] != '\0';)
			cmdline_args[k++] = flname[s++];
		cmdline_args[k] = '\0';
	}
	run_stat = save_stat = true;
	outchange(false);
	return false;
}

static void outchange(bool outchange_stat)
{
	if (outchange_stat)
		if (lan > L1_run && lan != NOT_SUPT)
		{
			cout << "\nFeature Not Supported. . . \n";
		}
		else
		{
			cout << "\n(without WhiteSpaces)\nEnter Ouput Name: ";
			cin >> outname;
		}
	// ADD COMPILE COMMAND HERE & SET "run_stat"
	switch (lan)
	{
	case c:
		strcpy(cmdrn, ccmd);
		strcat(cmdrn, outname);
		strcat(cmdrn, " ");
		strcat(cmdrn, flname);
		break;
	case cpp:
		strcpy(cmdrn, cpcmd);
		strcat(cmdrn, outname);
		strcat(cmdrn, " ");
		strcat(cmdrn, flname);
		break;
	case java:
		strcpy(cmdrn, jcmd);
		strcat(cmdrn, flname);
		break;
	case py:
		strcpy(cmdrn, "start python ");
		strcat(cmdrn, flname);
		run_stat = false;
		break;
	case kt:
		strcpy(cmdrn, "kotlinc ");
		strcat(cmdrn, flname);
		strcat(cmdrn, " -include-runtime -d ");
		strcat(cmdrn, outname);
		strcat(cmdrn, ".jar");
	}
	//  ADD EXECUTION COMMANDS HERE
	strcpy(run, "start ");
	if (lan == java)
	{
		strcat(run, "java ");
		strcat(run, outname);
	}
	else if (lan == kt)
	{
		strcat(run, "java -jar ");
		strcat(run, outname);
		strcat(run, ".jar");
	}
	else
		strcat(run, outname);
	if (arg_count)
	{
		strcat(run, " ");
		check_options();
	}
}

static void runapp()
{
	if (customcmd_count)
	{
		char temp[30];
		for (int i = 0; i < customcmd_count; ++i)
		{
			strcpy(temp, customcmd_lines[i].c_str());
			cout << ": " << temp << "\n";
			if (system(temp))
			{
				BringWindowToTop(hWnd);
				beep();
			}
		}
	}
	else
	{
		cout << "\n #Running App. . .\n: " << run << endl;
		if (system(run))
		{
			BringWindowToTop(hWnd);
			beep();
		}
	}
}

static inline int customcmd()
{
	theme_call();
	cout << "\nEnter Command Line:\n- ";
	fflush(stdin);
	cin.getline(cmdrn, sizeof(cmdrn));
	lan == NOT_SUPT;
	run_stat = false;
	customcmd_count = 0;
	for (int i = 0; i < 10; i++)
	{
		cout << "\nWould you like to add more Commands? (Y/N)- ";
		char check = getch();
		if (check == 'y' || check == 'Y')
		{
			customcmd_count++;
			cout << "\nEnter Command Line:\n- ";
			getline(cin, customcmd_lines[i]);
		}
		else
			break;
	}
	return 0;
}

static void autosave()
{
	keybd_event(VK_CONTROL, 0x9d, 0, 0);				   // Ctrl ~Press
	keybd_event(VkKeyScan('S'), 0x9f, 0, 0);			   // ‘S’ ~Press
	keybd_event(VkKeyScan('S'), 0x9f, KEYEVENTF_KEYUP, 0); // ‘S’ Release
	keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0);	   // Ctrl Release
	Sleep(500);
}

static void key_change()
{
	char ch;
	cout << "\n(SELECT A UNUSED 'FUNCTION' KEY ONLY)\nF11 & F12 are Not Supported || (Press ESC to Restore Default)";
back:
	cout << "\nPress any 'Function' Key: ";
	ch = getch();
	if (ch == 0 || ch == 224)
	{
		ch = getch();
		if (ch == 59)
		{
			key = VK_F1;
			strcpy(trigger_key, "F1");
		}
		else if (ch == 60)
		{
			key = VK_F2;
			strcpy(trigger_key, "F2");
		}
		else if (ch == 61)
		{
			key = VK_F3;
			strcpy(trigger_key, "F3");
		}
		else if (ch == 62)
		{
			key = VK_F4;
			strcpy(trigger_key, "F4");
		}
		else if (ch == 63)
		{
			key = VK_F5;
			strcpy(trigger_key, "F5");
		}
		else if (ch == 64)
		{
			key = VK_F6;
			strcpy(trigger_key, "F6");
		}
		else if (ch == 65)
		{
			key = VK_F7;
			strcpy(trigger_key, "F7");
		}
		else if (ch == 66)
		{
			key = VK_F8;
			strcpy(trigger_key, "F8");
		}
		else if (ch == 67)
		{
			key = VK_F9;
			strcpy(trigger_key, "F9");
		}
		else if (ch == 68)
		{
			key = VK_F10;
			strcpy(trigger_key, "F10");
		}
		else
		{
		invalid:
			cout << "\n #Invalid Key. . .\n";
			goto back;
		}
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		fflush(stdin);
		;
		key = VK_F5;
		cout << "\n #Restored Default Key 'F5'";
		return;
	}
	else
		goto invalid;
	cout << "\n\n #Trigger Key set to: " << trigger_key << endl;
	fflush(stdin);
	;
	sleep(1);
}

static inline void theme_change()
{
	cout << "\nTheme:\t(Press Enter to apply)\n 1. White on Black\n 2. Green on Black\n 3. Black on White\n 4. Black on Gray\n 5. Disco?";
	while (1)
	{
		theme_temp = theme;
		theme = getch();
		if (theme == '\n' || theme == 13)
		{
			theme = theme_temp;
			break;
		}
		theme_call();
	}
	fflush(stdin);
	switch (theme)
	{
	case '1':
	case '2':
		colr[6] = '0';
		colw[6] = '0';
		coly[6] = '0';
		colb[6] = '0';
		colg[6] = '0';
		break;
	case '3':
		colr[6] = '7';
		colw[6] = '7';
		coly[6] = '7';
		colb[6] = '7';
		colg[6] = '7';
		break;
	case '4':
		colr[6] = '8';
		colw[6] = '8';
		coly[6] = '8';
		colb[6] = '8';
		colg[6] = '8';
		break;
	}
}

static inline void theme_call()
{
	switch (theme)
	{
	case '1':
		system("color 0f");
		break;
	case '2':
		system("color 0a");
		break;
	case '3':
		system("color 70");
		break;
	case '4':
		system("color 80");
		break;
	case '5':
		for (int i = 0; i < 10; i++)
		{
			system("color a0");
			Sleep(75);
			system("color 60");
			Sleep(75);
			system("color 90");
			Sleep(75);
		}
		theme = theme_temp;
		theme_call();
		break;
	default:
		theme = theme_temp;
		cout << "\nInvalid Choice. .";
	}
}

static void key_change_arg(string setFkey)
{
	if (setFkey == "1")
	{
		key = VK_F1;
		strcpy(trigger_key, "F1");
	}
	else if (setFkey == "2")
	{
		key = VK_F2;
		strcpy(trigger_key, "F2");
	}
	else if (setFkey == "3")
	{
		key = VK_F3;
		strcpy(trigger_key, "F3");
	}
	else if (setFkey == "4")
	{
		key = VK_F4;
		strcpy(trigger_key, "F4");
	}
	else if (setFkey == "5")
	{
		key = VK_F5;
		strcpy(trigger_key, "F5");
	}
	else if (setFkey == "6")
	{
		key = VK_F6;
		strcpy(trigger_key, "F6");
	}
	else if (setFkey == "7")
	{
		key = VK_F7;
		strcpy(trigger_key, "F7");
	}
	else if (setFkey == "8")
	{
		key = VK_F8;
		strcpy(trigger_key, "F8");
	}
	else if (setFkey == "9")
	{
		key = VK_F9;
		strcpy(trigger_key, "F9");
	}
	else if (setFkey == "10")
	{
		key = VK_F10;
		strcpy(trigger_key, "F10");
	}
	else
	{
		cout << "\n #Invalid Function Key! (Using Deafault). . .\n";
		return;
	}
	cout << "#Trigger Key Changed to: " << trigger_key << endl;
}

static void tip()
{
	SetConsoleTitle("Auto Comp & Execution - $@n");
	system("cls");
	RECT ConsoleRect;
	GetWindowRect(hWnd, &ConsoleRect);
	MoveWindow(hWnd, ConsoleRect.left, ConsoleRect.top, 720, 420, TRUE);
	cout << "\t\t**Auto compile and Execution**\t\t-$@n\n";
	cout << " #How TO:#\nThis program automates the process of Saving, Compiling and Execution in one click.\n..(When using Editors like 'SUBLIME' etc) Triggers 'CTRL + S' to Auto Save.\n..Place this file, where the code is present.\n..Enter File Name with Extension.\n..In case of Extension mismatch, you are offered to add custom command line.\n..You can minimize this app or let it run in background.\n..Auto App LAUNCH can be toggled.\n..If compile time errors are found, the app automatically notifies the user.\n..Press '" << trigger_key << "' to initiate.\n\n";
}