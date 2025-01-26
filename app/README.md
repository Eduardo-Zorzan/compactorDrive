This app is a file manager that allows users to compress files using WinRAR while still being able to view and manage them in a UI more easily and efficiently than the default WinRAR interface.

The app was developed in C++ using the ImGui library, alongside GLFW for rendering the application, and WinRAR command-line tools to compress and decompress files. To store file data between app uses, a series of functions were implemented to save the data in a .txt file.

To handle the processing of compression and decompression alongside ImGui rendering, multithreading was implemented, allowing both processes to run simultaneously.

The main objective of developing this app was to gain a deeper understanding of C++, low-level programming techniques, and progremming and debugging in Visual Studio.

To run the app, simply download or clone the repository, ensure that WinRAR is installed on your system, and add WinRAR to the Windows Path environment, for that last requirement, you can follow the tutorial at the following link: https://cects.com/using-the-winrar-command-line-tools-in-windows/.