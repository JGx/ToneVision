function sendCallBack(){
	console.log("shit was sent");
}


var convertStringToArrayBuffer=function(str) {
  var buf=new ArrayBuffer(str.length);
  var bufView=new Uint8Array(buf);
  for (var i=0; i<str.length; i++) {
    bufView[i]=str.charCodeAt(i);
  }
  return buf;
}

var onSend = function(send){
	console.log("dumbass function yo");
}

var writeToPort = function(connection) {
	chrome.serial.send(connection.connectionId,convertStringToArrayBuffer("1"),onSend);
}

var onGetDevices = function(ports) {
    var eligiblePort = ports.filter(function(port) {
    	//Hardcoding serial port -- NEED TO CHANGE
    	return port.path.match(/\/dev\/tty.usb/);
  	});
  	//connect and write to port
  	chrome.serial.connect(eligiblePort[0].path, {bitrate:9600}, writeToPort);
}


chrome.serial.getDevices(onGetDevices);

//internal prototype for representing a sound module
function Node(moduleTypeNum, output){
  this.moduleTypeNum = moduleTypeNum;
  this.outputs = [];
  this.outputs.push(output);
};

//helper function for serialize()
function getConnections(curNodeID){
  console.log("getting connections");
  //obtain list of all connections
  var connectionList = jsPlumb.getConnections(); 
  console.log(connectionList);
  //nodes List is a dictionary of node entries
  var nodesList = [];
  $(connectionList).each(function(index,value){
    console.log("index is "+ index);
    //create new instance in nodelist if the connection's
    //source module hasn't been registered yet
    var id = value.sourceId;
    console.log("id is " + id);
    var output = value.target.parentNode.id;
    console.log("new output node is " + output);
    console.log("nodesList so far is " + nodesList);
    if(!(id in nodesList)){
      var modTypeId = getModuleTypeNumFromId(id);
      nodesList[id] = new Node(modTypeId,output);
    } else{
      //add this connection's target to its source's entry's output list
      nodesList[id].outputs.push(value.target.parentNode.id);
    }
  });
  console.log("Printing out list of node Ids");
  console.log(nodesList);
  return nodesList;
  //$(this).find('._jsPlumb_endpoint_anchor_').each(function(i,e){
}

//serializes the schema
//currently logs it to textarea
//TODO: send it over serial port to Arduino
function serialize(){
  console.log("serializing");
  //Traverse "tree" of sound modules
  //start at input module, go depth first preorder
  connectionsList = getConnections();
  //parse the connections list from getOutputs

  moduleList = [];

  $(connectionsList).each(function(moduleId,value){
    if( moduleId != 1){

      var module = connectionsList[moduleId];
      var string ="modTypeNum: " +  module.moduleTypeNum + ", id: " + moduleId +", module: " + $("#"+moduleId).text() + ", outputs:";
      //for each output, append it to the string and finally close with a period
      console.log(string);
      $(module.outputs).each(function(id,val){
        string += " " + val;
      });
      string += ";"
      moduleList.push(string);
    }
  });

  //print out schema in appropriate format in textarea
  $textArea.val(moduleList);

}