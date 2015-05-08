// Document ready
$(document).ready(function(){
	initializeVariables();
	initializeDraggables();
	instantiateInputAndOutputModules();
	initializeDroppable();
	initializeJsPlumb();
});

//args: none
//return value: none
//contract: initialize global variables that identify useful DOM elements
var $modules;
var $moduleBlocks;
var $canvas;
var $textArea;
var inputCol;	
var outputCol;
var paramRow;
var paramBox;
var moduleTypeNumHash = {};
var maxDivId = 1;

function initializeVariables(){
	//initialize selectorvariables
	$modules = $('.module');
	$canvas = $('#canvas');	
	$moduleBlocks = $('.moduleBlock');
	$textArea = $('#serial-textarea');
	inputCol="inputCol";
	outputCol="outputCol";
	paramRow="paramRow";
	paramBox="paramBox";

	//Hash is used to determine the number type of a module from its name
	moduleTypeNumHash['Input'] = 0;
	moduleTypeNumHash['Output'] = 1;
	moduleTypeNumHash['Gain'] = 2;
	moduleTypeNumHash['Filter'] = 3;
	moduleTypeNumHash['Delay'] = 4;
	moduleTypeNumHash['Oscillator'] = 5;
	moduleTypeNumHash['Compressor'] = 6;
	moduleTypeNumHash['Summer'] = 7;

	//Add chrome app compatible button callbacks
	$("#serialize-button").mouseup(serialize);
	$("#clear-button").mouseup(clearModules);
}

function getModuleTypeNumFromId(idNum){
	//Obtain the module type ID from the CSS ID of a sound module
	return moduleTypeNumHash[$("#"+idNum).text()];
}


var jsplumb;
var common;
function initializeJsPlumb(){
	//JSPlumb is the Connections plugin. Instantiate it with appropriate CSS
	jsPlumb.ready(function(){
		jsplumb = jsPlumb.getInstance();
		jsPlumb.setContainer($("#canvas"));
		jsPlumb.Defaults.PaintStyle = { strokeStyle:"#F09E30", lineWidth:2, dashstyle: '3 3', };
		jsPlumb.Defaults.EndpointStyle = { radius:7, fillStyle:"#F09E30" };
		jsPlumb.importDefaults({Connector : [ "Bezier", { curviness:50 } ]});
	});
}

//TODO: CHANGE HELPER OBJECT to be stylized
function initializeDraggables(){
	//Apply jQuery UI's draggable to menu (list) of sound modules
	$modules.draggable({
		helper:"clone"
	});
}

function instantiateInputAndOutputModules(){
	//Create the appropriate draggable input and output DOM elements
	var $input = $("<div>").addClass("moduleBlock").attr("id","0").text("Input");
	var $output = $("<div>").addClass("moduleBlock").attr("id","1").text("Output");
	$canvas.append($input);
	$canvas.append($output);
	$input.css({"top":$canvas.height() / 2 - $input.height() / 2});
	$output.css({"top":$canvas.height() / 2 - $input.height() / 2});
	$output.css({"left":$canvas.width() - 50 - $output.width() / 2});
	makeDraggable("#0");
	makeDraggable("#1");
	addHandles($input);
	addHandles($output);
}


//TODO: ADD CONFIRMATION ALERT
//NOTE: Chrome-app requires event callbacks to be objects
var clearModules = function clearModules(){
	//Clears the schema of all sound module elements except for input and output
	for (var d = 2; d <= maxDivId; d++) {
		console.log("removing divs")
		$("#"+d).remove();
	};
	i = 2; maxDivId =1; //update 
}

//NOTE: Function to be called on every soundmodule after it is appeneded to the canvas
function makeDraggable(divID){
	//Apply jQuery UI's draggable to divID's div
	//Update jsPlumb's connection position on element drag
	jsPlumb.draggable($(divID));
	$(divID).draggable({
            containment: 'parent',
            drag:function(e){
	    	   	$(this).find('._jsPlumb_endpoint_anchor_').each(function(i,e){ 
                    if($(e).hasClass(inputCol)){
                        jsPlumb.repaint($(e).parent());
                        console.log("repainting the input col");
                    }
                    else{
                    	console.log("trying to repaint");
                        jsPlumb.repaint($(e));
                    }
				});										
            }
        });
}



var i=2;
//TODO: sanitize droppable objects thru accept field
function initializeDroppable(){
	//Apply jQuery UI's droppable to the canvas and allow all draggable objects to be dropped onto canvas
	$canvas.droppable({
		accept: $modules,
		drop: function(event,ui){
			//get the module type and 'cast it' to module block div
			var $moduleType = $(ui.draggable).text();

			//var $soundModuleBlock = $("<div>").addClass('moduleBlock').attr('id',i).text($moduleType);

			//instantiate react class from reactModules.js
			var $soundModuleBlock = 
			 		React.render(React.createElement(BaseModule, {moduleName:$moduleType}), document.getElementById("canvas"));

			//append the div to the canvas and make draggable
			$canvas.append($soundModuleBlock);
			//try to append at the correct location
			var pos = ui.helper.position();
			var trueLeft = $canvas.width() + pos.left;
			$soundModuleBlock.css({"top":pos.top, "left":trueLeft}); 

			makeDraggable("#"+i);
			addHandles($soundModuleBlock);
			//use i for ID. Need to be smarter!
			i++;
			maxDivId++;
		}
	});
}


//TODO: resizing of textarea should be false
function addHandles(block){
	//Append appropriate input/output/parameter divs to all soundmodules

	//determine if block supports parameters
	var type = block.text();
	var divID = "#"+block.attr('id');
	console.log("div id is " + divID);

	//add input and output columns to all blocks
	/*
	var divsInput = $("<div>").addClass(inputCol);
	$(divID).append(divsInput);
	var divsOutput = $("<div>").addClass(outputCol);
	$(divID).append(divsOutput);*/

	//Custom parameter handles for all divs
	//CURRENTLY SUPPORTING:
	//    DELAY
	if(type == "Delay"){
		//add form for parameters with 2 input boxes
		var paramForm = $("<form>").addClass("form-inline");
		block.append(paramForm);

		var delayMinVal = $("<div>").addClass(paramBox);
		delayMinVal.attr('id',"param1");
		paramForm.append(delayMinVal);
		var textArea = $("<textarea>").attr("readonly",true).text("1");

		delayMinVal.append(textArea);

		var delayMaxVal = $("<div>").addClass(paramBox);
		delayMaxVal.attr('id',"param2");
		paramForm.append(delayMaxVal);

	}

	//Instantiate JSPlumb connections on input and output columns
	/*
	jsPlumb.makeSource(divsOutput, {
		parent: $(divID),
		anchor: 'Continuous'
    });
    jsPlumb.makeTarget(divsInput, {
    	anchor: 'Continuous'
    });*/
}

















