# Unreal Engine 4 Physics Example
*Unreal Engine version: 4.15*

An Unreal Engine sample project showing how to use substepping.<br>
This example is part of this article: http://www.aclockworkberry.com/unreal-engine-substepping/

This project contains a simple actor with a cube static mesh component. 
The cube component listens for substep ticks and simulates a damped spring force model at each substep.
An in-game debug panel shows the current render frame rate and the period and amplitude of the cube's oscillation. You can change the spring parameters or disable the substepping using the exposed editor properties of the actor.
With the default parameters, the oscillation will explode when the substepping is disabled.

The cube component registers also a secondary post-physics tick function.

![example 1](https://raw.githubusercontent.com/gportelli/UEPhysicsExample/master/Demo.gif)
