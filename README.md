OKSCE: One-Key-Save-Compile-Execute (Support: Windows) (Auto Save Enabled)
================================================
  [Download Latest!](https://github.com/san-vm/OKSCE-One-Key-Save-Compile-Execute/releases/)  
  
Currently supported languages:  
1. C  
2. CPP  
3. Java  
4. Python  
5. Kotlin  
  
  **(OR)** Add Multiple Custom Commands to run  
.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.  

Save, compile and run it in one key. Keep it running in background, make changes to code, Press 'F5' (Trigger key can be changed) to Auto Save the code, compile, and run.  
Now you can also add multiple Custom commands and run it all in a click.  
#### *NOTE*: This is not a compiler to any language.!  

Pre-req:
=======

..Make sure you have Required Compiler(s) installed;  
..Environment path is set correctly;  
..You can launch the app through cmd, pass arguments;  
.. -cus = cusotm command  
.. OKSCE 'filename' 'arguments'  

What / How TO:
=======

..This program automates the process of Saving, Compiling and Execution in one click.  
..(When using Editors like 'SUBLIME' etc) Triggers 'CTRL + S' to Auto Save.  
..Place this file, where the code is present.  
..Enter File Name with Extension.  
..In case of Extension mismatch, you are offered to add custom command line. (Can also add Multiple Custom commands)  
..You can let it run in background.  
..If compile time errors are found, the app automatically notifies the user.  
..Auto Save, Auto App LAUNCH can be toggled.  
..Press 'F5' to initiate. (Trigger Key can be changed)  
  

What it does:
=======

C: ```gcc -o 'filename' 'filename'.c```  
CPP: ```g++ -o 'filename' 'filename'.cpp```  
Java: ```javac 'filename'.java```  
Python: ```python 'filename'.py```  
Kotlin: (compile) ```kotlinc 'filename'.kt -include-runtime -d 'filename'.jar``` || (exc) ```java -jar 'filename'.jar```  
  
Usage:
=======

1> Enter File name:  
filename.ext arg1 arg2 arg3..  
-cus *to add custom commands*..  

2> Command Line:  
OKSCE.exe [OPTIONS] [VALUE | ARGS]  
OKSCE.exe -cus dir -cus -fkey f9  
## Adds the custom (-cus) command to the list; -cus follwed by -fkey changes Trigger key.