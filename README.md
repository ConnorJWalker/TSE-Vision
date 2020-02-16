## Getting Started
To build this project you need to [download and install cmake](https://cmake.org/download/). In a console in the projects directory run 

```
cmake .
```

This will generate the necassary Cmake files need for the project as well as creating the Visual Studio sln files. If using visual studio, build and run the program from visual studio. If you are linux use the following command
```
make
```

### Differences from previous projects
OpenCV uses different include directories to add it to the code. To cleanly get around this, common includes have been added to depenencies/opencv.h with a check to see the OS it is on. To add OpenCV to files add this line of code

```
#include <opencv.h>
```