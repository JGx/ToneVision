/*Serializes the schema and transfers it to the stompbox using Chrome App's serial API
*/

function sendCallBack(){
}


var convertStringToArrayBuffer=function(str) {

  var arr = [];
  for(var i=0; i<str.length; ++i){
    arr.push(str.charCodeAt(i));
  }
  console.log("arr is: " + arr);
  uint = new Uint8Array(arr);
  console.log("uint is: " + uint);
  return uint.buffer;
}

var convertArrayBufferToString=function(buf) {
  console.log("connverted array b 2 str");
  var bufView = new Uint8Array(buf);
  var encodedString = String.fromCharCode.apply(null, bufView);
  return decodeURIComponent(escape(encodedString));

}

var onSend = function(send){
	console.log("dumbass function yo");
}

var writeToPort = function(str_data) {
  console.log("writingToPort");
	chrome.serial.send(connectionId.connectionId,convertStringToArrayBuffer(str_data),onSend);
}


var connectionId;
var connectToPort = function(connection) {
  console.log("connected to serial port successfully.");
  connectionId = connection;
}

var dataReadFromPort = function(info){
  var str;
  //read from buffer
   if (info.connectionId == connectionId && info.data){
      str = convertArrayBufferToString(info.data);
      if (str.charAt(str.length-1) === '\n') {
        stringReceived += str.substring(0, str.length-1);
        onLineReceived(stringReceived);
        stringReceived = '';
      } else {
        stringReceived += str;
      }

     //print out buffer to console
     console.log("Port says:\n" + str);
   }
}

var onGetDevices = function(ports) {
    var eligiblePort = ports.filter(function(port) {
    	//Hardcoding serial port
    	return port.path.match(/\/dev\/tty.usb/);
  	});
  	//connect and write to port
  	chrome.serial.connect(eligiblePort[0].path, {bitrate:9600}, connectToPort);
    //assign callback for reading data from serial port
    chrome.serial.onReceive.addListener(dataReadFromPort);
}


chrome.serial.getDevices(onGetDevices);



//internal prototype for representing a connection
function ConnectionNode(sid,tid){
  this.sourceId = sid;
  this.targetId = tid;
}


//return list of ConnectionNodes
function getConnections(curNodeID){
  console.log("getting connections");
  //obtain list of all connections
  var connectionList = jsPlumb.getConnections(); 
  //nodes List is a dictionary of connection node entries
  var nodesList = [];
  $(connectionList).each(function(index,value){
    var sid = value.sourceId;
    var tid = value.target.parentNode.id;
    nodesList.push(new ConnectionNode(sid,tid));
  });
  console.log("Printing out list of node Ids");
  console.log(nodesList);
  return nodesList;
}


//Has module type id, input net ids and output net ids
function ModuleNode(mtid,inid,onid){
  this.moduleTypeId = mtid;
  this.inputNets = [];
  this.outputNets = [];
  if (inid != null){
    this.inputNets.push(inid);
  }
  if (onid != null){
    this.outputNets.push(onid);
  }
}

function getSerializedModulesNodes(){
  //Returns a list of module nodes (Defined above) based on the schema
  //Does this by converting the connections (source and target ids) into module nodes (type ids, input and output nets)


  //PROCEDURE:
  //obtain a list of all module type ids in order with their input nets and output nets
  /*
    Go through each connection:
      -Obtain its source id.
        -Use source_id as an index in a connections list which will hold another list of moduleTypeId, input Nets, and output Nets
          -That index's output Net will be the id of the connection
      -Obtain its target's id.
        -Use target_id as an index in the connection list
          -That index's input Net will be id of the connection

    INVARIANTS:
      -If source id is 0 (input module), connection ID must be zero
      -If target id is 1 (output module), connection ID must be 1
  */

  var connectionsList = getConnections();
  serializedModules = [];//<-- Used to hold data for all 3 output lists
  $(connectionsList).each(function(id,node){
    //extract source and target ids
    var sid = node.sourceId;
    var tid = node.targetId;
    //make a new Module node based on source id
    connectionID = sid;
    if(tid==1){
      connectionID = tid;//for output
    }

    //If sound module doesn't exist
    if(serializedModules[sid] == null){
      serializedModules[sid] = 
        new ModuleNode(getModuleTypeNumFromId(sid),null,connectionID);
    } else{
      //add to output nets
      serializedModules[sid].outputNets.push(connectionID);
    }

    //make new Module node based on target id
    if(serializedModules[tid] == null){
      serializedModules[tid] = new ModuleNode(getModuleTypeNumFromId(tid),
                                              connectionID,null);
    } else{
      serializedModules[tid].inputNets.push(connectionID);
    }

  });

  return serializedModules;
}






//send module list over the serial port to the arduino
function sendToArduino(moduleList){
  //first send number of sound modules and wait for arduino to acknowledge and confirm

  console.log(moduleList);
  writeToPort(moduleList);
  //writeToPort(String(moduleList.length));
}


