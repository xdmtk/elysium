import os, subprocess, time
import datetime,sys 

users = ['xdmtk', 'nick', 'erick', 'sebastian', 'daniel', 'josh']
root_path = '/'


def get_logs_to_delete():
    fresh_logs = generate_time_strings()
    all_logs = os.listdir(os.getcwd())
    return list(set(all_logs) - set(fresh_logs))

def generate_time_strings():
    time_strings = []
    now = datetime.date.today()
    for x in range(0,4):
        before = now - datetime.timedelta(x)
        time_struct = before.timetuple()
        time_strings.append(str(time_struct.tm_mon).zfill(2) + '-' 
                + str(time_struct.tm_mday).zfill(2) + '-'
                + str(time_struct.tm_year).zfill(2) + '.log')
    return time_strings

def verify_directory():
    return os.getcwd().split('/')[-1:][0] == '.elysium-logs'


def remove_stale_logs():
    if not verify_directory():
        print("Problem descending into user log directory")
        return
    log_list = get_logs_to_delete()

    for log in log_list:
        subprocess.call(['rm', log])

def main():

    for user in users:
        try:
            os.chdir(os.path.join(root_path, 'home', user, '.elysium-logs'))
            remove_stale_logs()
        except:
            pass

main()
