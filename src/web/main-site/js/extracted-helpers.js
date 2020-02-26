// Index of random shader loader
const shadercount = 0;
const scrollSpeed = 125;
const colorShiftSpeed= 10;

// Returns text from file on the server
function loadFile(filePath) {
      var result = null;
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.open("GET", filePath, false);
          xmlhttp.send();
          if (xmlhttp.status==200) {
                  result = xmlhttp.responseText;
                    }
            return result;
}
