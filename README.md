# dll_injection_in_small_program

====== IMPORTANT WARNING! ======  
This is a project related to DLL injection in programs and reverse engineering, and it only works on Windows OS (it won't work in other operating systems). Therefore, in order to test this program, you most likely need to disable everything related to security: firewall, antiviruses, all of it must be disabled (you can enable it back after testing, of course). Please keep that in mind before running the program and its DLL.  
However, I guarantee that there is no malicious code in this project at all that could possibly harm your computer (otherwise I wouldn't be uploading it to Github!). The Windows operating system very correctly tries to protect you in any way it can from external threats, and so reverse-engineering using this OS or trying to inject DLLs may be a bit of a hassle sometimes.  
Finally, nothing illegal is being done in this project. This is 100% ethical hacking, as the program that is being hacked is both written by myself and open-source. Ethical hacking should be used only and exclusively for situations such as reverse engineering software whose source code has been lost (for example, if the company that built that software asks), malware analysis for protection purposes, creating mods for videogames (as long as it is not illegal to do so), and other situations where no malicious intent is involved.  

====== HOW TO RUN ======  
1) Git clone this repository.  
2) Double-click on main_program.exe and run it. It's a small command-line battle program where you (the player) always loses. Check that it works fine (contact me if it doesn't: https://www.linkedin.com/in/antonio-de-odilon-brito-a052241b9/).  
3) Download Extreme Injector (be sure to have everything security-related deactivated at this point): https://www.extremeinjector.com  
4) Run main_program.exe again, and this time don't press any keys in it followed by Enter (if you do, make sure you don't get to the end of it, otherwise you won't see the DLL hack in action).  
5) Run Extreme Injector.  
	a) In "Process Name:" select the window that corresponds to main_program.exe.
	b) Press "Add DLL" and select the DLL. Navigate to the folder where you git cloned the repository. The DLL is in the following path: ".../DLLModifiesBattleProgram/Release/DLLModifiesBattleProgram.dll". Select the DLLModifiesBattleProgram.dll file.  
6) A few MessageBox windows should appear with messages saying that the DLL injection was successful. If the injection was not successful, double check the steps before to see if you've done everything right (contact me if it still isn't working!).  
7) Continue running main_program.exe - from now on, the player will always win!  
8) If you want to rebuild main_program and/or the DLL, install:  
	a) GCC (https://gcc.gnu.org/) to build main_program.c  
	b) ... and Visual Studio, as well as the C++-related tools to build the DLL.  
	c) You will very likely need to reverse-engineer the executable generated by compiling main_program.c using a decompiler like x64dbg in order to find the related addresses. Then you will need to modify the FirstEnhAttack() and SecondNoEnemyAttack() functions accordingly and make any other changes necessary in the DLL's source code.  

====== OVERVIEW AND DESCRIPTION ======  
The main program is, by design, very simple: the player starts with health and attack points that are much smaller than her/his enemy's, and both cause damage to each other at every loop. And since there is no variation in terms of those values (for example, no function to randomize values is called), then the player will always lose. Therefore, the only possible way for the player to win is if the program is hacked.  
By reverse engineering the program using x64dbg, I was able to identify the CPU registers and sections of memory related to the player's and the enemy's attack points, as well as create a code cave in the binary accordingly with the DLL. Therefore, modifications were made that increased the player's attack to 20, while the enemy's attack was set to zero. Thus, the player always hits the enemy for 20 damage, while the enemy's attack is always ineffective.  
Finally, most of the strings that are printed on the screen weren't modified in the hack: often times the program will print one information about attack and health, while the actual values are different.  

====== MOTIVATION FOR WRITING THE PROGRAM ======  
This simple program was an exercise in my reverse engineering skills. As a programmer who focuses on the low-level, I believe it is important to understand how machines work, and to see that work in action by reading its instructions in binary format with the help of tools such as x64dbg, which translate these instructions to Assembly code. I don't believe, however, that in most real-world cases a low-level programmer should know Assembly in depth, or even write actual real-world programs in Assembly; the C, C++, Rust etc compilers already do a fantastic job in generating efficient and optimized instructions for the machines! However, I do believe there are scenarios where this very low-level knowledge is useful in the real world: for example, in order for a company to be able to protect its software, often times it needs to know if there are any vulnerabilities in it, and so it may ask part of this security team to simulate an attack against it. And a successful attack simulation can help the company figure out where and how exactly it can generate better defenses for its software!  
