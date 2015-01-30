
// Document ready
$(document).ready(function(){
	//initialize the variable names to identify DOM elements
	initializeVariables();
	//take care of gridster's columns and rows
	initializeGridster();
	//initialize all sound modules to be draggable
	initializeDraggables();
	//initialize canvas to be droppable
	initializeDroppable();
});

//args: none
//return value: none
//contract: initialize global variables that identify useful DOM elements
var $modules;
var $canvas;
var gridster;
var jsplumb;
function initializeVariables(){
	$modules = $('.module');
	$canvas = $('#canvas');

	var connection = null;
	var common;
	console.log("connection's value is " + connection);
	jsPlumb.ready(function(){
		console.log("jsplumb is ready in the scripts.js");
		jsplumb = jsPlumb.getInstance();
		common = {
  			anchors:[ "BottomCenter", "TopCenter" ],
  			endpoints:["Dot", "Blank" ]
		};
		jsplumb.draggable("input");
		connection = jsplumb.connect({source:"input",target:"output"}, common);
	});


	//create grid
	gridster = $(".gridster ul").gridster({
        widget_margins: [5, 5],
        widget_base_dimensions: [100, 55],
        draggable: {
        	start: function(e, ui, $widget) {
              console.log('START position');
            },

            drag: function(e, ui, $widget) {
              console.log("dragging");
              
              if(connection!=null){
              	console.log("detaching connection");
              	jsPlumb.detach(connection);
              	connection = null;
              } else{
              	console.log("recreating connection");
              	connection = jsplumb.connect({source:"input",target:"output"}, common);
              }
            },

            stop: function(e, ui, $widget) {
              console.log("stopped");
            }
        }
    }).data("gridster");


	
}

function initializeGridster(){
	//currently have static size
	gridster.options.min_cols = 10;
	gridster.options.max_cols = 10;
	gridster.options.extra_rows = 10;
    console.log("min cols of gridster is" + gridster.options.min_cols);
    console.log("max cols of gridster is" + gridster.options.max_cols);
    console.log("extra rows of gridster is" + gridster.options.extra_rows);

    //add input and output blocks
    gridster.add_faux_rows(5);
	gridster.add_widget("<li id='input'>Input</li>", 1, 1, 1, 5);
	gridster.add_widget("<li id='output'>Output</li>", 1, 1, 9, 1);
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
}

//args: none
//return value: none
//contract: initialize the canvas to accept draggable sound modules
function initializeDroppable(){

	console.log("canvas of length: " + $canvas.length);

	//set canvas to accept draggable sound modules
	//NEED: have canvas manage a list of all accepted modules and support
	// rearrangement
	$canvas.droppable({
		accept: $modules,
		drop: function(event,ui){
			//get the module type and 'cast it' to module block div
			var $moduleType = $(ui.draggable).text();
			//OLD DIV CODE
			/*
			var $soundModuleBlock = ("<div class='moduleBlock'>"+$moduleType+"</div>");
			//append the div to the canvas...for now
			$canvas.append($soundModuleBlock);*/

			//NEW GRIDSTER CODE
			gridster.add_widget("<li>"+$moduleType+"</li>", 1, 1);

		}
	});
}










