# Getting Started
To build this project you need to [download and install cmake](https://cmake.org/download/). In a console in the projects directory run ```cmake . ```

This will generate the necessary Cmake files need for the project as well as creating the Visual Studio sln files. If using visual studio, build and run the program from visual studio. If you are linux use the following command ```make ```

### Running the Application

The executable file for this program will be located in cmake-build-debug, run the program from the terminal and pass in the required parameters:

| Argument | Description | Required | Default |
|:--------:|:-----------:|:--------:|:-------:|
| -w \<number\> | How many columns the card grid should have | No | 5 |
| -h \<number\> | How many rows the card grid should have | No | 5|
| -o <filepath> | The filepath to the output text file | Yes | -
| -r | Tell the program if it should render or not | No | False |
| -render | " | " | " |

##### Example
```
./cmake-build-debug/vision.exe -r -w 4 -h 3 -o output.txt
```

This will launch the program creating for a playing card grid that is 4 wide and 3 high. The results of the program will be rendered to the screen and the detected cards will be written to output.txt in the current working directory

### Differences from previous projects
OpenCV uses different include directories to add it to the code. To cleanly get around this, common includes have been added to dependencies/opencv.h with a check to see the OS it is on. To add OpenCV to files add this line of code

```
#include <opencv.h>
```