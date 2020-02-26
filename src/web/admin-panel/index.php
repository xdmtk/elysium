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
		
	    $log_file_path = "/home/" . $user . "/.elysium-logs/" . date("m-d-Y", time()) . ".log";
            /* Get a file handle */
	    $log_handle = fopen($log_file_path, "r");

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

function output_server_status_css($instance_owner) {

	$instances = get_running_instances();	
	if ($instances[$instance_owner] === true) {
		echo "";
	}
	else {
		echo "server-offline";
	}
}
?>



<style>
.server-status-info p{
  margin:auto;
  padding:10px;
  margin-top:-10px;
  margin-left:-13px;
  font-weight:bold;
  text-align:center;
  font-size:18px;
}
.server-status-info{
  list-style-type: none;
  padding:15px;
  font-family:arial;
  margin:auto;
  text-align:center;
  border:1px solid lightgrey;
  border-radius:5px;
  display:inline-block;
  margin-top: 150px;
  
} 
.log-output-area {
    position: absolute;
  border:1px solid lightgrey;
  border-radius:5px;
    height: 600px;
    width: 60%;
    left: 332px;
    top: 17%;
overflow-y: scroll;
}
.server-status-info li{
  margin-left:15px;
  margin-right:20px;
  display:inline-block;
}

.server-status-info li:before{
  position:absolute;
  margin-left:-20px;
  width:15px;
  height:15px;
  background-color:#95f476;
  content:"";
  border-radius:10px;
}
.server-status-info .warning:before{
  background-color:orange;
}
.server-status-info .offline:before{
  background-color:red;
}
.server-rack a{
  text-decoration:none;
}
.server-rack{
      -webkit-box-sizing: border-box;
              box-sizing: border-box;
    background-color: #141616;
    width: 300px;
    height: auto;
    border-radius: 10px 10px 0px 0px;
    /*margin: 20px auto;*/
    position: relative;
  -webkit-box-shadow:0 31px 40px 0px rgba(0, 0, 0, 0.25);
          box-shadow:0 31px 40px 0px rgba(0, 0, 0, 0.25);
}
.server-rack:after{
width: 100%;
    height: 47px;
    background-color: #6e6d71;
    position: absolute;
    content: "";
    bottom: -27px;
    border-radius: 0px 0px 20px 20px;
    z-index: -1;

}
.server-rack .label{
    color: white;
    font-weight: bold;
    background-color: #575b5c;
    border-radius: 10px 10px 0 0;
    font-family: arial;
    text-align: center;
    padding: 12px !important;
    font-size: 13px;


}

.server-inner{
    border: 1px solid #9da1a6;
    background-color: #f4f4f4;
    border-radius: 5px 5px 0px 0px;
    height: auto;
    width: 90%;
    z-index: 99999;
    position: absolute;
    left: 50%;
    top: 50%;
    -webkit-transform: translate(-50%,-50%);
        -ms-transform: translate(-50%,-50%);
            transform: translate(-50%,-50%);
    overflow: hidden;
  -webkit-box-shadow:inset 1px 1px 3px 0px #848181;
          box-shadow:inset 1px 1px 3px 0px #848181;
}


.server{
margin-top: 10px;
    position: relative;
    width: 103%;
    left: -4px;
    border-radius: 5px;
    margin-bottom: 10px;
    height: 45px;
    background-color: #3a3a3a;
    -webkit-transition: all 0.3s ease;
    -o-transition: all 0.3s ease;
    transition: all 0.3s ease;
}

.server:hover{
  -webkit-transform:scale(1.1);
      -ms-transform:scale(1.1);
          transform:scale(1.1);
}
.server:hover .hdd{
   // background-color: #c5c5c5;
    -webkit-box-shadow: 1px 1px 2px 1px #3636366b;
            box-shadow: 1px 1px 2px 1px #3636366b;
}
.server:hover:before{
  background-color:white;
}
/*
.server:after{
    content: '';
    position: absolute;
    top: 42%;
    left: 84%;
    width: 52px;
    height: 10px;
    transform: rotate(90deg);
    background-color: #8d8d8d;
    border-radius: 3px;
    box-shadow: -1px 2px 1px #0000005e;

}*/
.server:before{
    content: '';
    position: absolute;
    top: 44%;
    left: -5%;
    width: 40px;
    height: 0px;
    -webkit-transform: rotate(90deg);
        -ms-transform: rotate(90deg);
            transform: rotate(90deg);
    background-color: #d6d6d6;
    border-radius: 6px;
    -webkit-box-shadow: 0px -1px 1px #3a3a3a;
            box-shadow: 0px -1px 1px #3a3a3a;

}
.hdd{
    -webkit-transition: all 0.3s ease;
    -o-transition: all 0.3s ease;
    transition: all 0.3s ease;
    position: absolute;
    top: 25%;
    right: -4px;
    border-radius: 2px;
    width: 51px;
    height: 21px;
    background-color: #dbdad8;
    -webkit-transform: rotate(90deg);
        -ms-transform: rotate(90deg);
            transform: rotate(90deg);
}
.hdd:before{
    content: '';
    position: absolute;
    top: 28%;
    left: 70%;
    width: 7px;
    border-radius: 19px;
    -webkit-box-shadow: 1px -2px 1px #5652526e;
            box-shadow: 1px -2px 1px #5652526e;
    height: 7px;
    background-color: #504c4c;
}
.hdd:after{
    content: '';
    position: absolute;
    top: 31%;
    left: 10%;
    width: 26px;
    height: 6px;
    background-color: #505050;
    border-radius: 10px;
    -webkit-box-shadow: inset 1px 1px 1px #2e2e2e;
            box-shadow: inset 1px 1px 1px #2e2e2e;
}
.server-info{
  text-align:center;
color: white;
    font-family: arial;
    position: absolute;
    left: 50%;
    top: 15%;
    -webkit-transform: translate(-50%,-50%);
        -ms-transform: translate(-50%,-50%);
            transform: translate(-50%,-50%);
}

.server-status{
  list-style-type:none;
  padding:0;
  margin-left:10px;
      -webkit-transform: rotate(90deg);
          -ms-transform: rotate(90deg);
              transform: rotate(90deg);
    position: absolute;
  top: -5px;
  z-index:999;
}
.server-status li{
    width: 6px;
  height: 6px;
  float: left;
  margin-left: 5px;
  margin-top: 10px;
  background: rgba(149,244,118,0.6);
    -webkit-animation: pattern1 0.14s linear infinite;

}
.server-status li:nth-child(2){
  -webkit-animation: pattern1 0.14s 0.02s linear infinite;
}

.server-status li:last-child{
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

.server-warning li{
  background-color:orange;
}
.server-warning li:first-child{
  -webkit-animation: pattern2 0.14s linear infinite;
  
animation: pattern2 0.14s linear infinite;
  
 
}

.server-warning li:nth-child(2){
  
  -webkit-animation: pattern2 0.14s 0.02s linear infinite;
animation: pattern2 0.14s 0.02s linear infinite;
}

.server-warning li:last-child{
  -webkit-animation: pattern2 0.14s 0.05s linear infinite;
animation: pattern2 0.14s 0.05s linear infinite;
}
@-webkit-keyframes pattern2{
  0%{
    background: rgba(245,190,0,0.6);
  }
  100%{
    background: rgba(245,190,0,1);
  }
}
.server-offline li{
  background-color:red;
}


.server-offline  li:first-child{
  -webkit-animation: pattern3 0.9s linear infinite;
}

.server-offline li:nth-child(2){
  -webkit-animation: pattern3 0.9s linear infinite;
}

.server-offline li:last-child{
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


.server-half-container{
    padding: 6px;
  width:auto;
    position: relative;
    height: 250px;
    background-color: #73c0d7;
    margin: auto -12px;
    border-radius: 6px;
    -webkit-box-sizing: border-box;
            box-sizing: border-box;


}
.half-server li,.full-server li,.half-bottom-server li{
  display:inline-block;
  width:calc(100%/9);
    border-radius:3px;
  position:relative;
  -webkit-transition:all 0.3s ease-in-out;
  -o-transition:all 0.3s ease-in-out;
  transition:all 0.3s ease-in-out;

}
.half-server li.active:hover,
.full-server li.active:hover,
.half-bottom-server li.active:hover{
  -webkit-transform:scale(1.1);
      -ms-transform:scale(1.1);
          transform:scale(1.1);
  background-color:#5c5a5a;
}
.half-server li p,.full-server li p,.half-bottom-server li p{
position: absolute;
    margin: 0px;
    z-index: 999;
    white-space: nowrap;
    top: 50%;
    left: 50%;
    padding: 0px;
    -webkit-transform: translate(-50%, -50%) rotate(-90deg);
        -ms-transform: translate(-50%, -50%) rotate(-90deg);
            transform: translate(-50%, -50%) rotate(-90deg);
  font-size:12px;
}

.half-bottom-server:hover{
  z-index: 99999;
}
.half-server:hover{
  z-index: 99999;
}
.full-server li p{
    font-size:18px;
}

.half-server li.active,
.half-bottom-server li.active{
  height:95%;
}
.full-server li.active{
    height:95%;
}
.full-server li.active{
  background-color:#3a3a3a;
}
.half-server li.active{
  background-color:#3a3a3a;
}
.half-bottom-server li.active{
  background-color:#3a3a3a;
}
.half-server,.half-bottom-server{
    list-style-type: none;
  display:block;
  height:48%;
  width:100%;
  padding:0px;
  margin:0px;
  position:absolute;
}
.full-server{
  list-style-type: none;
  display:block;
  height:100%;
  width:100%;
  padding:0px;
  margin:0px;
  position:absolute;
}
.half-bottom-server{
  bottom:0;
}
.half-server,.full-server,.half-bottom-server{
    width:95%;
}

.server-half-container .server-status{
  -webkit-transform:rotate(0deg);
      -ms-transform:rotate(0deg);
          transform:rotate(0deg);
    margin:0px;
}
.server-half-container .server-status li{
  width:6px !important
}

</style>


<head>
<script>

const logData = <?php echo json_encode(get_log_data()) ?>;

function outputLogData(user) {
	
	const outputArea = document.getElementById('log-output');
	outputArea.innerHTML = "";
	for (var i = 0; i < logData[user].length; i++) {
		outputArea.innerHTML = outputArea.innerHTML + logData[user][i] + "<br>";
	}
}


</script>


<ul class="server-status-info">
    <center><p> Server Status</p></center>
    <li>Running</li>
    <li class="warning">Warning</li>
    <li class="offline">Offline</li>
</ul>

<div class="container">
    <div id="log-output" class="log-output-area">
    </div>
    <div class="server-rack">
        <P class="label"</P>

        <a href="#/">
            <div class="server" onclick="outputLogData('master')">
	    <ul class="server-status <?php output_server_status_css('master') ?> ">
                    <li></li>
                    <li></li>
                    <li></li>
                </ul>
                <p class="server-info">Master</p>
                <div class="hdd"></div>
            </div>
        </a>


        <a href="#/">
            <div class="server" onclick="outputLogData('erick')">
                <ul class="server-status <?php output_server_status_css('erick') ?> ">
                    <li></li>
                    <li></li>
                    <li></li>
                </ul>
                <p class="server-info">Erick</p>
                <div class="hdd"></div>
            </div>
        </a>

        <a href="#/">
            <div class="server" onclick="outputLogData('daniel')">
                <ul class="server-status <?php output_server_status_css('daniel') ?>">
                    <li></li>
                    <li></li>
                    <li></li>
                </ul>
                <p class="server-info">Daniel</p>
                <div class="hdd"></div>
            </div>
        </a>

        <a href="#/">
            <div class="server" onclick="outputLogData('josh')">
                <ul class="server-status <?php output_server_status_css('josh') ?>">
                    <li></li>
                    <li></li>
                    <li></li>
                </ul>
                <p class="server-info">Josh</p>
                <div class="hdd"></div>
            </div>
        </a>

        <a href="#/">
            <div class="server" onclick="outputLogData('nick')">
                <ul class="server-status <?php output_server_status_css('nick') ?>">
                    <li></li>
                    <li></li>
                    <li></li>
                </ul>
                <p class="server-info">Nick</p>
                <div class="hdd"></div>
            </div>
        </a>

        <a href="#/">
            <div class="server" onclick="outputLogData('sebastian')">
                <ul class="server-status <?php output_server_status_css('sebastian') ?>">
                    <li></li>
                    <li></li>
                    <li></li>
                </ul>
                <p class="server-info">Sebastian</p>
                <div class="hdd"></div>
            </div>
        </a>


    </div>
</div>
