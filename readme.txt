To run a stage go to the files directory and type:
player eval.cfg

To make a stage return correct positions of the objects in the world, it is necessary to drag and drop every object. It is not sufficient to just click on them. You need to move these objects at least one centimetre, also these can be moved back to the original position.

To compile a code go to the files directory and type:
g++ -o run main.cpp `pkg-config --libs --cflags opencv playerc++`

To run a code type:
./run

Due to problems at departmental machines, Player/Stage window was intentionally changed to 200x200 px in config files. Increasing size of Player/Stage window or zooming out, visibly affects the speed in which Player/Stage responses. As we focused on the speed in our robot, it is extremely vulnerable to the P/S' response time. In other words, increasing P/S window or zooming out will cause the robot to hit a wall due to out of date position. However, we would like to notice, that robot works fine at full size window and any zoom level at non-departmental machines.



Below we have enclosed more informations about run options and files produced:

By default map will be both saved and displayed once it is finished. You can modify display options (including displaying map at the time of exploration) using different arguments. To see them all type:
./run -help

We recommend using below command to run the code:
./run -atend 0 -robsize 2 -path -footprints -walls 1

Once robot finishes mapping and returns to it starting position, it saves an image with user defined options and displays that image with default display options. After displayed window is closed, it is also saved. File names are operating system date at the time of saving.



Due to technical problems, we were unable to produce screenshots of evaluation using built-in Player/Stage feature. We have used external program instead.