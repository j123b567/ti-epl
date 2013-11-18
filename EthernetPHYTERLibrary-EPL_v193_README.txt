EPL_v193_README.txt

Thank you for downloading the EPL Software Library.  This software library is an 
example how to integrate support for National's line of Ethernet PHYTER products 
including DP83640 with IEEE1588 PTP Support.

For a complete description of the EPL and associated development environment,
users are referred to the "PHYTER Software Development Guide."  For the 
latest information on the EPL please refer to the bottom of this file in the 
section "EPL Software Specific Notes".  



For more information on how to use the DP83640 and IEEE1588 PTP please refer 
to the following application notes:
  AN-1963:  IEEE 1588 Synchronization Over Standard Networks Using the DP83640
  AN-1838:  IEEE 1588 Boundary Clock and Transparent Clock Implementation Using the DP83640
  AN-1729:  DP83640 IEEE 1588 PTP Synchronized Clock Output 
  AN-1728:  IEEE 1588 Precision Time Protocol Time Synchronization Performance

These and all other National Semiconductor Application Notes can be found at:
http://www.national.com/apnotes/appnotes_all_2.html




EPL Software Specific Notes

Known Issues:
-------------
NOTE:  There ARE some issues with EPL_v193_20091022.zip package which are 
fairly easy to deal with.  The main issues are:
1)  Python 2.4 is a build environment requirement.  This is something that I 
    missed in the SDG update but the current code is structured such that it is 
    required.  This is because EPL provides an interface for the Python based ALP 
    framework.  This COULD be removed with a few clever #ifdefs and build 
    configurations and maybe if we do another major release I'll look into it.  
    For now people simply need to install python 2.4.4 ( available at python.org )
    When Python is properly installed python24.dll gets installed into 
    Windows\system32 so it really isn't needed in the project directories.

2) Opal Kelly USB drivers are required to provide access to the H/W that the 
   API we used in okFrontPanel.dll requires.  These are easiest to install using 
   the FrontPanel-Win-3.0.3.exe found in the ALP Tools package.  NOTE:  The 
   version of OK driver installed and okFrontPanel.dll/.cpp/.h used to build 
   _epl.dll and made available to the applications is critical.  Any mismatch 
   in versions and it simply won't work.  All of the current ALP and EPL 
   releases assume v3.0.3 even though there are new versions available.  
   The newer versions WILL work but everything that uses them must be rebuilt 
   using the new files and the new driver and DLL need to be available at 
   runtime.  Moving to a new version CAN cause a lot of build error which can 
   easily be avoided (see below.)  Unless there is a specific reason to upgrade 
   it is easier to just use the version provided.

3) There are a couple of missing MS C runtime DLLs (MSVCP71.dll and 
   MSVCR71.dll) that the Opal Kelly API requires.  When properly installed 
   Opal Kelly places these in C:\Program Files\Opal Kelly\FrontPanel.  See 
   the "Running the Examples" section below for more on this.

Base Assumptions:
-----------------
- Clean development system (fresh XP SP3 all current patches etc.)  I list 
  SP3 and current patches not because I know of any particular issue or 
  requirement it is just good practice and where I have tested.

- Using EPL_v193_20091023.zip as delivered.

System Setup Process:
---------------------
- Install Python 2.4.4 - All the default options are fine.  The projects in 
  the current ZIP assume that Python will be installed in C:\Program Files\Python24 
  which is the recommendation in the ALP Framework setup document.  I prefer to 
  leave it go to C:\Python24 myself but that requires a change to the project 
  configurations (see the "Building the DLL and Examples" section below.)
- Install Opal Kelly Front Panel v3.0.3 software
- Plug in the board.
- Unzip EPL_xxxxxxxxxxx.zip to wherever you want.  For the purposes of this, 
  I will assume they are extracted into C:\EPL.

Running the Examples:
---------------------
- Switch to the C:\EPL\OS\Windows\EPLTestApp directory.
- Assuming you have the updated release file or manually deleted the files 
  noted in the "Known Issues" section #4 above all you have to do is run by 
  typing the following command:  .\Debug\EPLTestApp.exe -h  This will start the 
  program and display the help/version message.  On the other hand you COULD 
  copy the necessary DLL and BIT files to the Debug directory, switch into the 
  Debug directory, and run the application from there.  If you follow this model 
  you must be sure that the files are properly maintained when the build, 
  release, and/or version control system cleans the directory.
- PTPTestApp.exe is run exactly the same way from it's directory.

Building the DLL and Examples:
------------------------------
- Assuming the System Setup Process above has been followed you need to 
  install some build tools in order to be able to rebuild the dll and/or examples.
- The SDG document the version of Visual Studio 2005 used to build the existing 
  binaries.  That is no longer true.  This version was built using 
  Visual Studio 2008 Express with SP1 that is available as a free download at: 
  http://www.microsoft.com/express/download  You can select the C++ or the all 
  in one disc image and just install the C++ option.  Again all you need is the 
  C++ portion and all the default setup options will work although you CAN 
  choose not to install the Silverlight runtime and MS SQL functionality to 
  save some time/space.  Once properly installed the following should be noted:
  1) When you build you may see a couple warnings about /Wp64 being deprecated 
     in the newer version.  You can simply ignore this or go into the project 
	 properties and change the 
	 "C/C++ - General - Detect 64-bit Portability Issues" option to 
	 "No" or "Inherit from parent..."

- The projects should build without errors if you have followed 
  the steps above.
  
- Keep in mind that if you rebuild the DLL you need to make sure that the 
  updated DLL gets copied into all the right spots as a mismatch in DLL can 
  cause confusion and unexpected behavior.

Updated Release Files:
----------------------
- To account for some of the issues listed above the following files are available:
1) EPL_v193_Docs.zip.
This is just the 2 PDFs that were part of the original ZIP

2) EPL_v193_20091023.zip.  

3) EPL_v193_README.txt.  This file!


Other Notes:
------------
- If you use a newer version of the Opal Kelly S/W you may encounter a lot of 
  build errors when you start to use the new okFrontPanel.cpp/.h files.  This 
  is due to the include of windows.h which attempts to bring in EVERYTHING for 
  windows.  This can be avoided by adding #define WIN32_LEAN_AND_MEAN just 
  before the #include <windows.h> at the top of okFrontPanelDLL.h as follows:
    #if defined(_WIN32)
         #define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers
         #include <windows.h>
    #elif defined(LINUX)
    #elif defined(MACOSX)
    #endif
This works up to the current version v3.1.0

- Again, if you attempt to move to the new version you have to make sure that 
  all versions of the driver, dlls, and assorted files get updated.  There are 
  a number of related OK Python files that must be updated within the ALP 
  Framework that must also be updated.
