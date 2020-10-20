Operational Control with iCub
=============================

[![Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/vvv-school/assignment_make-it-roll)

# Prerequisites
By now, you should be an expert of the following components :wink::
- [Cartesian Control](http://www.icub.org/doc/icub-main/icub_cartesian_interface.html).
- [Gaze Control](http://www.icub.org/doc/icub-main/icub_gaze_interface.html).

# Assignment
We want you to develop a rather simple module that employs the `Cartesian Interface`
and the `Gaze Interface` to accomplish the following tasks:

1. Make iCub **look down at the table**.
1. **Detect the blue ball** in both image planes.
1. Retrieve the **ball position** in the Cartesian domain.
1. Let iCub **look at the ball**.
1. Finally, ask iCub to reach for the ball and **make it roll**.

This assignment is peculiar in that **we can interface the simulator and the real robot indifferently**.

The outcome should look like the animation below:

<p align="center">
  <img src="/assets/make-it-roll.gif"/>
</p>

Some of the points reported above have been already addressed in the code (e.g. [**detection of the blue ball**](./src/main.cpp#L41-L71)), so you need to **fill in the missing gaps** highlighted by the comment `// FILL IN THE CODE` in the [**`src/main.cpp`**](./src/main.cpp) module.

⚠️ Don't require the operational controllers to perform too fast movements: you will find yourself tuning up your code to make it run on the real robot smoothly.

Once done, you can test your code in two ways:

1. **Manually**: running the _yarpmanager scripts_ provided from within [**app/scripts**](./app/scripts) and yielding corresponding commands to the _module rpc port_.
1. **Automatically**: [running the script **test.sh**](https://github.com/vvv-school/vvv-school.github.io/blob/master/instructions/how-to-run-smoke-tests.md) in the **smoke-test** directory. Take into account these important points:
    1. We use a **timeout of _120 seconds_** to check the status of rpc communication, meaning that you have _120 seconds_ max to accomplish each rpc command.
    1. When you reply to rpc commands, we assume the robot has **finished the movement**.
    1. The smoke-test will add a little random displacement to the initial position of the ball :wink:

If you pass the test on the simulator, 🕒 book the robot 🤖 to get a real experience!

# [How to complete the assignment](https://github.com/vvv-school/vvv-school.github.io/blob/master/instructions/how-to-complete-assignments.md)
