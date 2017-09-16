【Note】
	Demos are developed by Qt on CentOS. The following example uses CentOS system to illustrate how to use the Demo, other Linux systems refer to CentOS system.
	

If .so files and executable file are under the same directory, please use the library files under the same directory. This maybe something wrong that cannont find *.so. Please follow below:
export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./


If they are not under the same directory, the directories of the above files need to load into dynamic library search path. Here are several ways to configure: 

1. Add all the dynamic library paths of the network SDK into LD_LIBRARY_PATH environment variable. 

1) Input in the terminal (only valid for current user):
export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/XXX

2)  Modify  ~/.bashrc  or  ~/.bash_profile. Add the following line at the end:
export  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/XXX
Save the file and execute it by (only valid for the current user):  source  .bashrc

3) Modify /etc/profile. Add the same line as that in 1-2). Save the file and execute it by source command (only valid for the current user).  

2. Add the path of SDK at the end of file /etc/ld.so.conf, such as /XXX . Save the file and execute ldconfig.

3. Put the SDK library under /lib64 、/lib or usr/lib64、usr/lib

4. Use  -Wl,-rpath to assign dynamic path in Makefile. libdhnetsdk.so file needs to load using –l. 
As an example, -Wl,-rpath=/XXX: -ldhnetsdk  


Please note that we highly suggest you to put library files under the same directory. If not, the above method one and two are recommended. 
