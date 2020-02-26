<?php

function get_running_instances() {

    /* Initialize k/v for server instance owners */
    $running_instances = [
        'master' => false,
        'daniel' => false,
        'erick' => false,
        'josh' => false,
        'nick' => false,
        'sebastian' => false,
    ];

    /* Get the output of ps aux and separate into output lines */
    $ps_aux = explode("\n", shell_exec("ps aux | grep \"elysium\""));

    /* Iterate the lines */
    foreach ($ps_aux as $process_line) {

        /* Explode into fields delimited by spaces */
        $ps_fields = explode( " ", $process_line);

        /* Iterate fields */
        foreach ($ps_fields as $field) {

            /* If elysium-server is running, get the owner's username */
            if ($field == "./elysium-server") {
                $owner = $ps_fields[0];

                /* xdmtk account runs the master instance */
                if ($owner == "xdmtk") {
                    $owner = "master";
                }

                /* Set the instance k/v true if found */
                $running_instances[$owner] = true;
            }
        }
    }

    return $running_instances;
}

function get_log_data() {

    /* Setup k/v of user->log data array */
    $log_data = [
        'master' => [],
        'daniel' => [],
        'erick' => [],
        'josh' => [],
        'nick' => [],
        'sebastian' => [],
    ];

    /* Setup unix users */
    $users = ['xdmtk', 'daniel' . 'erick', 'josh', 'nick', 'sebastian'];

    /* Grab the correct log file (filename is stamped by UTC time) */
    date_default_timezone_set('UTC');

    /* Iterate users */
    foreach ($users as $user) {

        /* Check to see if log directory exists */
        if (is_dir("/home/" . $user . "/.elysium-logs")) {

            /* Get a file handle */
            $log_handle = fopen("/home/" . $user . "/.elysium-logs/" . date("m-d-Y", time()));

            /* Master instance runs on user xdmtk */
            if ($user == "xdmtk") {
                $user = "master";
            }

            /* Process log lines and append to corresponding array in $log_data */
            while (($line = fgets($log_handle)) !== false) {
                array_push($log_data[$user], $line);
            }
        }
    }

    return $log_data;
}
