# Getting Started
To build this project you need to [download and install cmake](https://cmake.org/download/). In a console in the projects directory run ```cmake . ```

This will generate the necessary Cmake files need for the project as well as creating the Visual Studio sln files. If using visual studio, build and run the program from visual studio. If you are linux use the following command ```make ```

### Potential Problems and Fixes

> No arguments have been entered

This program expects at minimum the output filepath to be enter as a argument on startup, with extra optional arguments available (see below). If not are passed in then the program will output this error and stop running.

To fix this on Visual Studio, right click on ```vision``` in solution explorer and then add the required parameters to ```Properties > Configuration Properties > Debugging > Command Arguments``` 

> Unable to start program '\<filepath\>\\ALL_BUILD'
>
> The system cannot find the file specified

This error message means that the wrong project has been set as startup project by Visual Studio. To fix this, right click on ```vision``` in solution explorer and click ```Set as StartUp Project```. Rebuild the project and it should now run successfully.

### Running the Application

The executable file for this program will be located in cmake-build-debug, run the program from the terminal and pass in the required parameters:

| Argument | Description | Required | Default |
|:--------:|:-----------:|:--------:|:-------:|
| -w \<number\> | How many columns the card grid should have | No | 5 |
| -h \<number\> | How many rows the card grid should have | No | 5|
| -o \<filepath\> | The filepath to the output text file | Yes | -
| -r | Tell the program if it should render or not | No | False |
| -render | " | " | " |

#### Example
```
./cmake-build-debug/vision.exe -r -w 4 -h 3 -o output.txt
```

This will launch the program creating for a playing card grid that is 4 wide and 3 high. The results of the program will be rendered to the screen and the detected cards will be written to output.txt in the current working directory

### Differences from previous projects
OpenCV uses different include directories to add it to the code. To cleanly get around this, common includes have been added to dependencies/opencv.h with a check to see the OS it is on. To add OpenCV to files add this line of code

```
#include <opencv.h>
```