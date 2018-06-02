#SystemC Quick Installation Guide
## Download SystemC 
### Works on any version of Visual Studio
1. Download the SystemC source code (systemc-2.3.1.tgz) from http://www.accellera.org/.

2. Untar the downloaded file to the directory where SystemC is to be installed.
e.g. D:\systemc-2.3.1

3. Make a directory msvc14 and create a "Static library" Visual Studio 2015 project, systemc, under it.

4. Add the source files (*.cpp and *.h) under src directory and below (except those under src\sysc\packages and src\sysc\qt), to the systemc project.
(Use "Add → Existing Item" in Visual Studio. Alternatively, drag-and-dropping from Windows File Explorer to the Solution Explorer in Visual Studio also works.)

4-1. In my case, I temporarily moved src\sysc\packages and src\sysc\qt directories to outside of the SystemC directory hierarchy. Then I searched for *.cpp and *.h files under src directory in Windows File Explorer. Finally, I drag-and-dropped the searched file into the Solution Explorer in Visual Studio and moved back the two directories to their original locations.

5. Add src directory to "Additional Include Directories" of the systemc project.

6. Set "Enable Run-Time Type Info" of the systemc project to "Yes".

7. Add /vmg to "Additional Options" of the systemc project.
