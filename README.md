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

![make-it-roll](/misc/make-it-roll.gif)

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
- You can instead use this [**model**](https://github.com/robotology-playground/icub-gazebo-wholebody/tree/master/worlds/iCub_and_Table) within **Gazebo**.

# [How to complete the assignment](https://github.com/vvv-school/vvv-school.github.io/blob/master/instructions/how-to-complete-assignments.md)
