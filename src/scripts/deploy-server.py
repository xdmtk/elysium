import os,sys,subprocess

git_repo_url = 'https://github.com/xdmtk/elysium'

# Establish paths
home_path = '/home/'+os.getenv('USER')
deploy_path = home_path+'/server'
elysium_repo_path = home_path+'/elysium'
paths = [home_path, deploy_path, elysium_repo_path]

# Verify paths
for path in paths:
    if not os.path.exists(path) and path != elysium_repo_path:
        print('Bad path: ' + path) 
        exit(-1)
    # Clone the repo if user doesn't have it
    if not os.path.exists(path) and path == elysium_repo_path:
        os.chdir(home_path)
        subprocess.call(('git clone ' + git_repo_url).split(' '))


# Establish build paths
elysium_server_path = elysium_repo_path + '/src/server'
elysium_server_build_path = elysium_server_path + '/cmake-build-debug'

# Make build directory if doesn't exist
if not os.path.exists(elysium_server_build_path):
    os.mkdir(elysium_server_build_path)


# Pull latest
os.chdir(elysium_repo_path)
subprocess.call('git pull'.split(' '))

os.chdir(elysium_server_build_path)
subprocess.call('cmake ..'.split(' '))
subprocess.call('make')
subprocess.call(('mv elysium-server ' + deploy_path).split(' '))




