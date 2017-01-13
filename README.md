Operational Control with iCub
=============================

# Prerequisites
By now, you should be an expert of the following components :wink::
- [Cartesian Control](http://wiki.icub.org/iCub/main/dox/html/icub_cartesian_interface.html).
- [Gaze Control](http://wiki.icub.org/iCub/main/dox/html/icub_gaze_interface.html).

# Assignment
We want you to develop a rather simple module that employs the `Cartesian Interface`
and the `Gaze Interface` to accomplish the following tasks:

1. Make iCub **look down at the table**.
2. **Detect the blue ball** in both image planes.
3. Retrieve the **ball position** in the Cartesian domain.
4. Let iCub **look at the ball**.
5. Finally, ask iCub to reach for the ball and **make it roll**.

The outcome should look like the animation below:

![make-it-roll](/misc/make-it-roll.gif)

The [detection of the blue ball is **already available**](./src/main.cpp#L35-L65), so you need to fill in the missing gaps in the code regarding each of the remaining points illustrated above.

Once done, you can test your code in two ways:

1. **Manually**: running the _yarpmanager scripts_ provided from within [**app/scripts**](./app/scripts) and yielding corresponding commands to the _module rpc port_.
2. **Automatically**: [running the script **test.sh**](https://github.com/vvv-school/vvv-school.github.io/blob/master/instructions/how-to-run-smoke-tests.md) in the **smoke-test** directory. Note that we use a timeout of _60 s_ to check the status of rpc communication, meaning that you have _60 s_ max to accomplish each operation of the list above.

## Notes
- To make the blue ball show up within the simulator, you have to turn on the
flag **RENDER::objects** in the [**`iCub_parts_activation.ini`**](https://github.com/robotology/icub-main/blob/master/app/simConfig/conf/iCub_parts_activation.ini#L28) file.

    To do so, you could run the following **bash instructions**:
    ```sh
    context="simConfig"
    file="iCub_parts_activation.ini"

    # import the file for customization (don't print warnings)
    yarp-config context --import $context $file 2>&1 > /dev/null

    # find out where it's been saved (we're interested in just the first location)
    where=($(yarp-config context --where $context))

    # enable objects
    sed -i '/objects/c\objects on' $where/$file
    ```
    Also, you might find this [**resource**](https://github.com/robotology/QA/issues/42) quite useful to get accustomed with configuration files in Yarp :smiley:
- Alternatively, you can use this [**model**](https://github.com/robotology-playground/icub-gazebo-wholebody/tree/master/worlds/iCub_and_Table) within **Gazebo**. Be careful, the **smoke-test** does work only with iCub_SIM.

# [How to complete the assignment](https://github.com/vvv-school/vvv-school.github.io/blob/master/instructions/how-to-complete-assignments.md)
