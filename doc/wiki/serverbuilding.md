### Server Build Instructions

##### Required Tools
* Debian based Linux (Deployed on Ubuntu 18.04)
* `cmake`
* `make`

##### Building
* Add any new/additional source files to `CMakeLists.txt` 
* Run `cmake`
* Run `make`

On the EC2, you can execute the `deploy-server.py` script, which will run both `cmake`, `make`, and move the executable into the correct server directory.

##### Executing
* Locally there are no special instructions for executing the server
* On the server, execution can take place via normal CLI execution, or using `nohup` for unattended access (logging out of the server SSH session and having the server persist)


