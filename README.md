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
4. Ask iCub to reach for the ball and **make it roll**.

![snapshot](/misc/snapshot.png)

## Notes
- To make the blue ball show up within the simulator, you have to turn on the
**objects** flag in the **`iCub_parts_activation.ini`** file.

# How to complete the assignment
- **Students** are required to follow these instructions:
    1. To start, click on the **invitation link** that teachers emailed you. A **new repository** will be spawned from this one, where you can provide your solution.
    2. [Create a **new branch**](https://help.github.com/articles/creating-and-deleting-branches-within-your-repository/) from `master`; you may call it as your `username`.
    3. [**Clone**](http://gitref.org/creating/#clone) the repository to your computer.
    4. Fill in the **gaps** and [**commit**](http://gitref.org/basic/#commit) changes to complete your solution.
    5. [**Push**](http://gitref.org/remotes/#push)/sync the changes up to GitHub.
    6. [Create a **pull request**](https://help.github.com/articles/creating-a-pull-request) with `master` as _base branch_ and `username` as _compare branch_.
    7. Within the pull request, [**mention** any teacher](https://help.github.com/articles/basic-writing-and-formatting-syntax/#mentioning-users-and-teams) to turn in the assignment.
    8. Address the points the teacher highlighted by **pushing your fixes** and **replying to the comments** directly from within the pull request.
    9. **Don't merge** and **don't close** the pull request.

- **Teachers** are required to follow these instructions:
    1. Once created, you can then do [**code review**](https://help.github.com/articles/about-pull-request-reviews) with line-by-line feedback directly within the pull request.
    2. Within the pull request, try to provide also a **brief summary** touching general remarks such as:
        - Did the student **comment** the code sufficiently?
        - Is the code **cross-compilable**?
        - To which **extent** are the requirements accomplished?
    3. Once the student has positively addressed all the points, **close the pull request without merging**.

## Reviewing Notes for Teachers
In case the student **did not create a new branch**, you can still launch a PR based review by doing:

1. Identify within the student repository the **last commit of the starter code** (i.e. the last commit done by the teacher in the `master` branch).
2. Create a **new branch** from that commit; call it `review-teacherusername`.
3. Start a **pull request** with `review-teachernusername` as _base branch_ and `master` as _compare branch_.
4. You can now do **code review** as explained above.
