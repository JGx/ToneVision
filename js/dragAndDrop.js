// Document ready
$(document).ready(function(){
	//initialize the variable names to identify DOM elements
	initializeVariables();
	//initialize all sound modules to be draggable
	initializeDraggables();
	//initialize canvas to be droppable
	initializeDroppable();
	//initialize jsPlumb
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
var moduleTypeNumHash = {};

function initializeVariables(){
	$modules = $('.module');
	$canvas = $('#canvas');	
	$moduleBlocks = $('.moduleBlock');
	$textArea = $('#serial-textarea');
	inputCol="inputCol";
	outputCol="outputCol";

	//initialize hash of module id's
	moduleTypeNumHash['Input'] = 0;
	moduleTypeNumHash['Output'] = 1;
	moduleTypeNumHash['Gain'] = 2;
	moduleTypeNumHash['Filter'] = 3;
	moduleTypeNumHash['Delay'] = 4;
	moduleTypeNumHash['Oscillator'] = 5;
	moduleTypeNumHash['Compressor'] = 6;
	moduleTypeNumHash['Summer'] = 7;
}


var jsplumb;
var common;
function initializeJsPlumb(){
	jsPlumb.ready(function(){
		jsplumb = jsPlumb.getInstance();
		jsPlumb.setContainer($("#canvas"));
		jsPlumb.Defaults.PaintStyle = { strokeStyle:"#F09E30", lineWidth:2, dashstyle: '3 3', };
		jsPlumb.Defaults.EndpointStyle = { radius:7, fillStyle:"#F09E30" };
		jsPlumb.importDefaults({Connector : [ "Bezier", { curviness:50 } ]});
		//make all module blocks draggable

	});
}

//args: none
//return value: none
//contract: initialize all sound modules to be draggable objects
function initializeDraggables(){
	console.log("modules of length: " + $modules.length);

	//set draggable object to clone for now
	//NEED: change to image with module name
	$modules.draggable({
		helper:"clone"
	});
	// $moduleBlocks.draggable({
	// 	containment:"parent",
	// 	drag:function(e){
	// 		console.log("draggable module");
	// 		jsplumb.repaintEverything();                             
 //        }
	// });

	
}


function getModuleTypeNumFromId(idNum){
	return moduleTypeNumHash[$("#"+idNum).text()];
}

//args: none
//return value: none
//contract: initialize the canvas to accept draggable sound modules
var i=2;
function initializeDroppable(){

	console.log("canvas of length: " + $canvas.length);

	//create input and output blocks
	var $input = $("<div>").addClass("moduleBlock").attr("id","0").text("Input");
	var $output = $("<div>").addClass("moduleBlock").attr("id","1").text("Output");
	$canvas.append($input);
	$canvas.append($output);
	//allign the elements
	$input.css({"top":$canvas.height() / 2 - $input.height() / 2});
	$output.css({"top":$canvas.height() / 2 - $input.height() / 2});
	$output.css({"left":$canvas.width() - 50 - $output.width() / 2});
	makeDraggable("#0");
	makeDraggable("#1");


	//set canvas to accept draggable sound modules
	//NEED: have canvas manage a list of all accepted modules and support
	// rearrangement
	$canvas.droppable({
		accept: $modules,
		drop: function(event,ui){
			//get the module type and 'cast it' to module block div
			var $moduleType = $(ui.draggable).text();

			var $soundModuleBlock = $("<div>").addClass('moduleBlock').attr('id',i).text($moduleType);

			//append the div to the canvas and make draggable
			$canvas.append($soundModuleBlock);
			//try to append at the correct location
			var pos = ui.helper.position();
			var trueLeft = $canvas.width() + pos.left;
			console.log("pos top is:"+pos.top);
			$soundModuleBlock.css({"top":pos.top, "left":trueLeft});
			console.log("pos left is:"+trueLeft);

			makeDraggable("#"+i);
			//use i for ID. Need to be smarter!
			i++;
		}
	});
}

function makeDraggable(divID){

	//ensure that connections move on module dragging
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


	//add input and output columns
	var divsInput = $("<div>").addClass(inputCol);
	var divsOutput = $("<div>").addClass(outputCol);
	$(divID).append(divsInput);
	$(divID).append(divsOutput);
	//make output column a source
	jsPlumb.makeSource(divsOutput, {
		parent: $(divID),
		anchor: 'Continuous'
    });
	//make input column a target
    jsPlumb.makeTarget(divsInput, {
    	anchor: 'Continuous'
    });
}

















