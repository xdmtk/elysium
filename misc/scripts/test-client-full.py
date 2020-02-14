import curses, os, time
import socket, sys, serial
import signal, subprocess
from threading import Thread
import queue

Q = None
S = None
LT = None
COL = None
ROW = None
PORT = 'Elysium Server' 
INPUT_HEIGHT = None
TERM_CHR = '\n'
BAUD_RATE = 9600

ERROR = -1
MODE = 'normal'
LINE_BUFFER = ''
COMMAND_BUFFER = ''
LINE_POS_BEGIN = 2
USER_PROMPT = os.getenv('USER') + '@' + socket.gethostname()

serial_history = []
input_history = []

com_hist_mark = 0
quit_flag = None
b_count_w = 0
b_count_r = 0
scroll_counter = 0


def main(w):
    global Q
    global LT

    def clean_thread_exit(sig, frame):
        global quit_flag
        quit_flag = True
        curses.endwin()
        os._exit(1)

    signal.signal(signal.SIGINT, clean_thread_exit)

    draw_workspace(w)
    Q = queue.Queue()
    listener_thread = Thread(target=serial_listen, args=[w])
    LT = listener_thread
    listener_thread.start()
    set_insert_mode(w)
    while True:
        key_events(w)



def serial_listen(w):
    global quit_flag
    global S
    global b_count_r

    s = socket.socket()
    s.connect(('elysium-project.net', 6692))
    S = s
    while True:
        msg = s.recv(4096)
        Q.put(msg)
        write_history(w)
        b_count_r += len(msg)

# SECTION: MASTER KEY EVENTS
#############################################
###
#

def key_events(w):
    
    global com_hist_mark
    key = w.getch()
    if key == curses.KEY_RESIZE:
        w.erase()
        if draw_workspace(w) == ERROR:
            return
        write_history(w)
        return
    
    # Handle normal mode entries
    if MODE == 'normal':
        if key == ord(':'):
            enter_command(w)
        if key == ord('i'):
            set_insert_mode(w)
        if key == curses.KEY_NPAGE:
            scroll_text(w, 'down')
        if key == curses.KEY_PPAGE:
            scroll_text(w, 'up')

    # Handle insert mode entries
    elif MODE == 'insert':
        if key == 27:
            set_normal_mode(w)
        else:
            if key == curses.KEY_ENTER or key == 10:
                flush_input(w)
                com_hist_mark = 0
            else:
                process_input(w, key)



# SECTION: CURSES WRITERS
#############################################
###
#

def scroll_text(w, direction):
    
    global scroll_counter 

    limit = INPUT_HEIGHT - LINE_POS_BEGIN
    if len(serial_history) <= limit:
        return

    if direction == 'up':
        if scroll_counter <= len(serial_history) - limit:
            scroll_counter += 1
    elif direction == 'down':
        if scroll_counter != 0:
            scroll_counter -= 1

    write_history(w, False, scroll_counter)



def write_byte_count(w):

    (cur_y, cur_x) = curses.getsyx()

    # Starting position decided by len of r/w string
    start_pos = COL - len('RECV: XXX  -  WRITE: XXX')

    # Write received and written to upper right corner
    w.addstr(0, start_pos, 'RECV: ' + str(b_count_r).rjust(3) +
             '  -  WRITE: ' + str(b_count_w).rjust(3), curses.A_REVERSE | curses.A_BOLD)

    w.move(cur_y, cur_x)
    w.refresh()



def write_history(w, user_write=False, scroll = False):

    # Save current cursor position
    (cur_y, cur_x) = curses.getsyx()
    

    # Check for new entries from serial port into serial queue
    if Q.empty() is False:

        # Add all data from queue to the serial history list
        while Q.empty() is False:
            ser_response = None
            try:
                ser_response = Q.get().decode().replace('\n', '')
            except:
                ser_response = Q.get().replace('\n', '')
            serial_history.append(PORT + ' >> ' + str(ser_response))

    limit = (INPUT_HEIGHT - LINE_POS_BEGIN)
    line_start = 0 
    # line_start measures the amount of overflow lines in serial history
    # to determine for curses when to start writing text to the text area
    if len(serial_history) >= limit:
        
        line_start = len(serial_history) - (INPUT_HEIGHT - LINE_POS_BEGIN - 1)

    
    line_marker = 0
    line_pos = LINE_POS_BEGIN
    for line in serial_history:

        # Exit loop if maximum lines in text area have been written
        if limit == 1:
            break

        # If we have advanced in text area history, the line_start value 
        # will be the first message to print, and line_marker indicates 
        # the current iteration for serial history
        if line_start != 0 and line_marker < (line_start - scroll_counter):
            line_marker += 1
            continue
        
        # For every line written, subtract from limit
        limit -= 1

        # First clear the current line
        for y in range(2, COL - 1):
            w.addch(line_pos, y, ' ')

        # Then add line content and advance the line position
        w.addstr(line_pos, 1, line)
        line_pos += 1

    # If user sent message, move cursor back to input area
    if user_write is True:
        w.move(INPUT_HEIGHT, 2)

    # Otherwise return cursor to original position
    else:
        write_byte_count(w)
        w.move(cur_y, cur_x)


    w.refresh()


# SECTION: INSERT MODE INPUT
#############################################
###
#

def process_input(w, key):

    global LINE_BUFFER

    # Backspace logic for text entry
    if key == curses.KEY_BACKSPACE:
        (y, x) = curses.getsyx()
        if x == 2:
            return
        w.addch(y, x - 1, ' ')
        w.move(y, x - 1)
        LINE_BUFFER = LINE_BUFFER[:-1]
        w.refresh()
        return

    # Currently only key up works, cycling through
    # previous input
    elif key == curses.KEY_UP:
        write_input_history(w, 'up')
        return
    elif key == curses.KEY_DOWN:
        write_input_history(w, 'down')
        return

    # Silently ignore left and right keys
    elif key == curses.KEY_LEFT:
        return
    elif key == curses.KEY_RIGHT:
        return

    # Otherwise add to the line buffer and print it
    LINE_BUFFER += chr(key)
    w.addstr(INPUT_HEIGHT, 2, LINE_BUFFER)
    w.refresh()

def get_time():
    tm = time.gmtime(time.time())
    return ' [' + str(tm.tm_hour) + ':' + str(tm.tm_min) + ':' + str(tm.tm_sec) + ']'


def flush_input(w):

    global LINE_BUFFER
    global b_count_w
    
    # Add input to history 
    input_history.append(LINE_BUFFER)

    # Clear text area 
    for x in range(2, COL - 1):
        w.addch(INPUT_HEIGHT, x, ' ')

    # Only write to serial if port is specified
    if PORT is None:
        serial_history.append(USER_PROMPT + get_time() + ' >> ' + LINE_BUFFER)
        serial_history.append('No port/device specified!')
        write_history(w, True)
    
    # Record bytes written successfully
    else:
        b_written = 0
        try:
            S.sendall(bytes((LINE_BUFFER).encode('utf8')))
        except:
            serial_history.append('Failed to write to serial port')

        if b_written != 0:
            #serial_history.append(USER_PROMPT + LINE_BUFFER)
            write_history(w, True)

        # If no bytes are written, log error
        write_byte_count(w)

    LINE_BUFFER = ''



# SECTION: MODE SETTERS
#############################################
###
#

def set_normal_mode(w):

    global MODE

    # Remove insert label on top left
    w.addstr(0, 0, '      ', curses.A_REVERSE | curses.A_BOLD)
    w.refresh()
    MODE = 'normal'
    pass


def set_insert_mode(w):
   
    global MODE
    MODE = 'insert'

    # Add insert label
    w.addstr(0, 0, 'INSERT', curses.A_REVERSE | curses.A_BOLD)

    # Move cursor to text entry area
    w.move(INPUT_HEIGHT, 2 + len(LINE_BUFFER))
    curses.curs_set(1)
    w.refresh()


# SECTION: COMMAND ENTRY
#############################################
###
#

def enter_command(w):

    # Global containing current command
    global COMMAND_BUFFER

    # Make cursor visible
    curses.curs_set(1)

    # Clear out command entry area
    for x in range(0, COL):
        w.addch(ROW + 1, x, ' ')

    # Begin command buffer with entry character ':'
    # and print it
    COMMAND_BUFFER = ':'
    w.addstr(ROW + 1, 0, COMMAND_BUFFER)
    w.refresh()

    # Enter key entry loop
    key = w.getch()

    # Flush command on enter
    while key != curses.KEY_ENTER and key != 10:

        # Backspace logic ( move curses back and either 
        # keep cursor at begin on empty buffer )
        if key == curses.KEY_BACKSPACE:
            (y, x) = curses.getsyx()
            if x == 2:
                key = w.getch()
                continue

            # Or clear the buffer 1 character at a time and print it
            w.addch(y, x - 1, ' ')
            w.move(y, x - 1)

            COMMAND_BUFFER = COMMAND_BUFFER[:-1]
            key = w.getch()
            w.refresh()
            continue
        
        # Silently ignore keypad keys
        if key == curses.KEY_UP:
            key = w.getch()
            continue
        elif key == curses.KEY_DOWN:
            key = w.getch()
            continue
        elif key == curses.KEY_LEFT:
            key = w.getch()
            continue
        elif key == curses.KEY_RIGHT:
            key = w.getch()
            continue

        # If all passes, add key to buffer and print result
        COMMAND_BUFFER += chr(key)
        w.addstr(ROW + 1, 0, COMMAND_BUFFER)
        w.refresh()

        # Restart key grab
        key = w.getch()

    # On finish, jump to parse command
    parse_command(w)


def parse_command(w):
    global LINE_BUFFER
    global COMMAND_BUFFER
    global INPUT_HEIGHT
    global quit_flag
    global PORT
    global b_count_w 

    # For the few select commands, find special keys to parse
    if COMMAND_BUFFER.find('q') != -1:
        quit_flag = True
        quit()

    # For port entry
    elif COMMAND_BUFFER.find('port ') != -1:

        # Verify port exists
        if os.path.exists(COMMAND_BUFFER.split(' ')[1]):

            # Gets the second token in port command entry
            PORT = COMMAND_BUFFER.split(' ')[1]
            draw_workspace(w)

            # Now that we have the port, start the serial listening thread store
            # in global LT
            LT.start()
        
        # If port is invalid, print error
        else:
            w.addstr(ROW + 1, 0, 'Invalid port!')
            w.refresh()
            curses.curs_set(0)
            return

    # Parse bytes entered for byte entry command
    elif COMMAND_BUFFER.find('byte ') != -1:
        byte_str = COMMAND_BUFFER[6:]

        b_count_w_local = 0
        byte_str = byte_str.split(' ')
        for b in byte_str:
            b_count_w_local += S.write(bytearray([int(b)]))
        
        w.addstr(ROW+1, 0, 'Wrote ' + str(b_count_w_local) + ' bytes')
        w.refresh()
    
    elif COMMAND_BUFFER.find('help') != -1:
        print_help_page(w)
        draw_workspace(w)
        
    if COMMAND_BUFFER.find('byte ') == -1:
        # On enter, clear command entry area
        for x in range(0, len(COMMAND_BUFFER)):
            w.addch(ROW + 1, x, ' ')

        # Disappear cursor
        curses.curs_set(0)
        w.refresh()


# SECTION: CURSES FUNCTIONS
#############################################
###
#

def draw_workspace(w):
    global COL
    global ROW
    global INPUT_HEIGHT
   
    # Line drawing chars
    DH_LINE = '═'
    DU_RCOR = '╗'
    DU_LCOR = '╔'
    DL_LCOR = '╚'
    DL_RCOR = '╝'
    DV_LINE = '║'

    # Set the terminal height
    (ROW, COL) = w.getmaxyx()
    if (ROW < 15) or (COL < 40):
        w.clear()
        w.addstr(int(ROW/2), int(COL/2)-int(len('Screen size too small')/2) ,
                'Screen size too small')
        w.refresh()
        return ERROR

    # Leave space for command entry
    ROW -= 2
    COL -= 1

    # Set row number of text entry area
    INPUT_HEIGHT = ROW - 1

    # Set corners
    w.addch(1, 0, DU_LCOR)
    w.addch(1, COL, DU_RCOR)
    w.addch(ROW, 0, DL_LCOR)
    w.addch(ROW, COL, DL_RCOR)

    # Draw lines
    for x in range(1, COL):
        w.addch(1, x, DH_LINE)
        w.addch(ROW, x, DH_LINE)
        w.addch(ROW - 2, x, DH_LINE)
    for x in range(2, ROW):
        w.addch(x, 0, DV_LINE)
        w.addch(x, COL, DV_LINE)


    # Set title
    title = 'Elysium TUI Client'
    if PORT is None:
        title += ' - no host specified'
    else:
        title += ' - ' + str(PORT)

    # Set the length of title to determine center position in title bar
    l_title = len(title)
    y = 0
    for x in range(0, COL + 1):

        # Calcuate center of title bar
        if (x > (COL / 2) - (l_title / 2)) and (x < (COL / 2) + (l_title / 2)):
            w.addch(0, x, title[y], curses.A_REVERSE | curses.A_BOLD)
            y += 1
        else:
            w.addch(0, x, ' ', curses.A_REVERSE)


    w.move(0, 0)
    w.refresh()


# SECTION: HELP SECTION
#############################################
###
#

def print_help_page(w):
    
    w.erase()
    w.refresh()
    curses.endwin()
    print('\033[2J')
    help_page = '''
                                                                               
              █████   ██████  ████████  █████████████    ██████  ████████  
             ███░░   ███░░███░░███░░███░░███░░███░░███  ███░░███░░███░░███ 
            ░░█████ ░███████  ░███ ░░░  ░███ ░███ ░███ ░███ ░███ ░███ ░███ 
             ░░░░███░███░░░   ░███      ░███ ░███ ░███ ░███ ░███ ░███ ░███ 
             ██████ ░░██████  █████     █████░███ █████░░██████  ████ █████
            ░░░░░░   ░░░░░░  ░░░░░     ░░░░░ ░░░ ░░░░░  ░░░░░░  ░░░░ ░░░░░ 

                                    sermon v0.9.1 
                            https://github.com/xdmtk/sermon


NAME: 
     sermon - A curses-based serial monitor 

SYNOPSIS: 

    python3 sermon.py [ -p ] [ PORT ] [ -t ] [ TERMINATION CHAR ] [ -b ] [ BAUD RATE ] 

DESCRIPTION: 

    sermon is a light-weight curses-based terminal serial monitor used for reading and writing to serial ports. The sermon text 
    interface uses VIM inspired key bindings to switch between insert mode and command mode. 

    Command line usage allows optional specification of three arguments, namely the device port to open a serial connection
    on, the terminating character to send after submitting input to the serial device, and the baud rate. 


    -p  - Device port ( example: /dev/ttyUSB0 )

    -t  - Termination character ( Defaults to newline )
        
            nl -> Newline/line feed \'\\n\'

            cr -> Carriage return \'\\r\'

            nlcr -> Newline/linefeed * Carriage return \'\\n\\r\'

    -b  - Baud rate ( Defaults to 9600 )



COMMAND MODE:

    To begin entering commands, enter command mode using the ESC key and then open the command buffer by 
    typing the character ':' 


    PORT SPECIFICATION: 
        
        In command mode you can specify on the fly the serial port to read/write from by using the 'port' command. 
        
        Usage: port [ PORT ]
        Example: ( port /dev/ttyACM0 )

    
    WRITING RAW BYTES:

        In addition to entering ASCII range input, you can also write raw bytes directly to the device by using the 'byte' 
        command. 
       
        Usage: byte [ BYTE INTEGER VALUE ] 
        Example: byte 26  ( sends CTRL-Z ) 



CONTACT:

    sermon is under active development and still in beta stages. Usage is at your own risk. To report bugs, please open an 
    issue at https://github.com/xdmtk/sermon/issues

'''
    print(help_page)
    foo = input()








# SECTION: ARGUMENT FUNCTIONS
#############################################
###
#

def parse_args():
    global PORT
    global TERM_CHR
    global BAUD_RATE

    if len(sys.argv) > 1:
        for x in range(1, len(sys.argv)):

            # Arguemnt setting device port
            if sys.argv[x].find('-p') != -1:
                PORT = sys.argv[x + 1]
                x += 1
                continue
            
            # Argument to set termination character
            if sys.argv[x].find('-t') != -1:
                TERM_CHR = term_chr_parse(sys.argv[x + 1])
                x += 1
                continue

            # Argument to set baud rate
            if sys.argv[x].find('-b') != -1:
                try:
                    BAUD_RATE = int(sys.argv[x + 1])
                except Exception as e:
                    BAUD_RATE = ERROR
                x += 1
                continue


def validate_args():

    # Make sure device exists
    if PORT is not None:
        if os.path.exists(PORT) is False:
            return ERROR

    # Check baudrate and termination character 
    if TERM_CHR == ERROR or BAUD_RATE == ERROR:
        return ERROR


def term_chr_parse(arg):

    # Sets the termination char
    if arg == "nl":
        return '\n'
    if arg == "cr":
        return '\r'
    if arg == "nlcr":
        return '\n\r'
    else:
        return ERROR




def write_input_history(w, direction):
    global com_hist_mark
    global LINE_BUFFER

    com_hist_len = len(input_history)
    if com_hist_len == 0:
        return

    if direction == 'up':
        input_history.reverse()
        if (com_hist_len - com_hist_mark) <= 0:
            return

        LINE_BUFFER = input_history[com_hist_mark]
        com_hist_mark += 1
        input_history.reverse()

        for x in range(2, COL - 1):
            w.addch(INPUT_HEIGHT, x, ' ')
        w.addstr(INPUT_HEIGHT, 2, LINE_BUFFER)



parse_args()
os.environ.setdefault('ESCDELAY', '25')
curses.wrapper(main)
