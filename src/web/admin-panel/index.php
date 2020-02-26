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
?>

<style>
    @import url(https://fonts.googleapis.com/css?family=Lato:100,400);

    body{
        margin: 0;
        padding: 0;
        background: #eee;
    }

    .box{
        width: 250px;
        height: 200px;
        position: absolute;
        left: calc(50% - 125px);
        top: calc(50% - 100px);
        left: -webkit-calc(50% - 125px);
        top: -webkit-calc(50% - 100px);
    }

    .box span{
        font-family: 'Lato', sans-serif;
        font-weight: 300;
        font-size: 20px;
        position: absolute;
    }

    .box span:nth-child(2){
        top: 2px;
        left: 125px;
    }

    .box span:nth-child(7){
        top: 85px;
        left: 125px;
    }

    .box span:nth-child(12){
        top: 165px;
        left: 125px;
    }

    .server{
        width: 110px;
        height: 30px;
        background: #3a3a3a;
        border-radius: 1px;
    }

    .server ul{
        margin: 0;
        padding: 0;
        list-style: none;
    }

    .server:first-child ul li{
        width: 6px;
        height: 6px;
        float: left;
        margin-left: 10px;
        margin-top: 12px;
        background: rgba(149,244,118,0.6);
    }

    .server ul li:first-child{
        -webkit-animation: pattern1 0.14s linear infinite;
    }

    .server ul li:nth-child(2){
        -webkit-animation: pattern1 0.14s 0.02s linear infinite;
    }

    .server ul li:last-child{
        -webkit-animation: pattern1 0.14s 0.05s linear infinite;
    }

    @-webkit-keyframes pattern1{
        0%{
            background: rgba(149,244,118,0.6);
        }
        100%{
            background: rgba(149,244,118,1);
        }
    }

    .warning ul li{
        width: 6px;
        height: 6px;
        float: left;
        margin-left: 10px;
        margin-top: 12px;
        background: rgba(245,190,0,0.6);
    }

    .warning ul li:first-child{
        -webkit-animation: pattern2 0.14s linear infinite;
    }

    .warning ul li:nth-child(2){
        -webkit-animation: pattern2 0.14s 0.02s linear infinite;
    }

    .warning ul li:last-child{
        -webkit-animation: pattern2 0.14s 0.05s linear infinite;
    }

    @-webkit-keyframes pattern2{
        0%{
            background: rgba(245,190,0,0.6);
        }
        100%{
            background: rgba(245,190,0,1);
        }
    }

    .error ul li{
        width: 6px;
        height: 6px;
        float: left;
        margin-left: 10px;
        margin-top: 12px;
        background: rgba(236,69,62,0.6);
    }

    .error ul li:first-child{
        -webkit-animation: pattern3 0.9s linear infinite;
    }

    .error ul li:nth-child(2){
        -webkit-animation: pattern3 0.9s linear infinite;
    }

    .error ul li:last-child{
        -webkit-animation: pattern3 0.9s linear infinite;
    }

    @-webkit-keyframes pattern3{
        0%{
            background: rgba(236,69,62,0.6);
        }
        80%{
            background: rgba(236,69,62,0.6);
        }
        100%{
            background: rgba(236,69,62,1);
        }
    }
</style>



<ul class="server-status-info">
    <p> Server Status</p>
    <li>Running</li>
    <li class="warning">Warning</li>
    <li class="offline">Offline</li>
</ul>

<div class="server-rack">
    <P class="label"> COMPUTER CENTER</P>

    <a href="#/">
        <div class="server">
            <ul class="server-status ">
                <li></li>
                <li></li>
                <li></li>
            </ul>
            <p class="server-info">Server 1</p>
            <div class="hdd"></div>
        </div>
    </a>

    <a href="#/">
        <div class="server">
        </div>
    </a>

    <a href="#/">
        <div class="server">
            <ul class="server-status server-warning">
                <li></li>
                <li></li>
                <li></li>
            </ul>
            <p class="server-info">Server 2</p>
            <div class="hdd"></div>
        </div>
    </a>

    <a href="#/">
        <div class="server">
            <ul class="server-status server-offline">
                <li></li>
                <li></li>
                <li></li>
            </ul>
            <p class="server-info">Server 3</p>
            <div class="hdd"></div>
        </div>
    </a>

    <a href="#/">
        <div class="server">
            <ul class="server-status">
                <li></li>
                <li></li>
                <li></li>
            </ul>
            <p class="server-info">Server 4</p>
            <div class="hdd"></div>
        </div>
    </a>



    <div class="server-half-container">

        <ul class="half-server">

            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">half 2nd</p>
                </li>
            </a>
            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">first</p>
                </li>
            </a>
            <li></li>
            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">first new</p>
                </li>
            </a>
            <li></li>
        </ul>
        <ul class="half-bottom-server">

            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">first</p>
                </li>
            </a>
            <li></li>
            <a href="http://www.google.com" target="_blank">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">google</p>
                </li>
            </a>
            <li></li>
            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">bottom 2nd </p>
                </li>
            </a>
            <li></li>
        </ul>

        <ul class="full-server">

            <a href="#/">
                <li class="active">
                    <ul class="server-status server-warning">
                        <li></li>
                        <li></li>
                    </ul>

                    <p class="server-info">first</p>
                </li>
            </a>
            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info ">

                        warning</p>
                </li>
            </a>
            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">first</p>
                </li>
            </a>
            <a href="#/">
                <li class="active">
                    <ul class="server-status">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">first</p>
                </li>
            </a>
            <li></li>
            <a href="#/">
                <li class="active">
                    <ul class="server-status server-offline">
                        <li></li>
                        <li></li>
                    </ul>
                    <p class="server-info">first</p>
                </li>
            </a>
        </ul>

    </div>

</div>
