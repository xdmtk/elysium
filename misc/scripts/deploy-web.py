import os, sys, subprocess

# Path evaluation
git_url = 'https://gitlab.com/csun380spring2020/elysium'
user = os.environ.get('USER')
home_path = os.path.join('/', 'home', user)
git_path = os.path.join(home_path, 'elysium')
git_web_path = os.path.join(git_path, 'src/web/main-site')
git_admin_panel_path = os.path.join(git_path, 'src/web/admin-panel')
web_path = os.path.join(home_path, 'web')
master_site_path = '/var/www/html'
master_admin_path = '/var/www/html/admin'


# Clone the repo if it doesn't exist
if not os.path.exists(git_path):
    subprocess.call(['git', 'clone', git_url])

# CD to git repo
os.chdir(git_path)

# Pull
subprocess.call(['git', 'pull'])


if len(sys.argv) == 2 and sys.argv[1] == '-master' and os.geteuid == 0:

    # Remove existing master web directory
    subprocess.call(['rm', '-rf', master_site_path]) 

    # 
    subprocess.call(['cp', '-r', git_web_path, master_site_path]) 
    subprocess.call(['cp', '-r', git_admin_panel_path, master_admin_path]) 


else:
    # Remove existing web directory
    subprocess.call(['rm', '-rf', web_path])

    # Copy repo web directory to user web directory
    subprocess.call(['cp', '-r', git_web_path, web_path]) 
