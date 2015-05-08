


//Angular app that handles synchronization between internal schema representation and UI view of sound modules

var app = angular.module('plumbApp',[]);

//Controller creates  cthe internal schema module
//$scope is application object (owner of application vars/funcs)
app.controller('PlumbCtrl', function($scope) {

	//liModule represents an <li> sound module element
	//users drag the liModule onto the canvas and create a soundModule item
	/*type_id is unique to each soundModule class and used for serialization
	     0 and 1 are reserved for input and output, respectively
	*/
	//name is user-facing string shown on <li>
	//AngularJS Note: No correspondence between liModule functionName and liModule in ng-repeat="liModule in moduleList" directive!
	function liModule(type_id,name) {
		this.type_id = type_id;
		this.name = name;
	}

	//data members
	$scope.moduleList = []; //<-- stores all liModules
	$scope.mr_schema_uid = -3; //<-- most recent unique identifier for each module on canvas
	$scope.mr_net_id = 1; //<-- most recently used unique net id
	$scope.moduleNames = ['Delay','Gain','Summer','Filter','Envelope Follower'];

	/*
		Constructors for sound module schema objects
	*/

	function inputModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;
		this.type_id = -2;
		this.name = name;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
		this.inputNets = [];
		this.outputNets = [];
	}

	function outputModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;
		this.type_id = -1;
		this.name = name;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
		this.inputNets = [];
		this.outputNets = [];
	}

	function delayModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;
		this.type_id = 0;
		this.name = name;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
		this.numArgs = 2;
		this.minVal = 8000;
		this.val = 10000;
		this.maxVal = 15000;
		this.inputNets = [];
		this.outputNets = [];
		this.paramType = 0;
	}

	function gainModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;
		this.type_id = 1;
		this.name = name;
		this.numArgs = 2;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
		this.maxVal = 1;
		this.val = 1;
		this.gainTypes = ['Logarithmic','Linear'];
		this.gainType = 'Linear';
		this.inputNets = [];
		this.outputNets = [];
		this.paramType = 0;
	}

	function summerModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;
		this.type_id = 2;
		this.name = name;
		this.numArgs = 1;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
		this.inputNets = [];
		this.secondInputNet;
		this.paramType = 0;
		this.val = 0;
		this.outputNets = [];
	}

	function envelopeFollowerModule ( schema_id, name, pos_x, poy_y ){
		this.schema_id = schema_id;
		this.type_id = 3;
		this.name = name;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
	}

	function filterModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;
		this.type_id = 4;
		this.name = name;
		this.numArgs = 0;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
		this.val = 1000;
		this.inputNets = [];
		this.outputNets = [];
		this.paramType = 0;
	}


	function oscillatorModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;

		this.name = name;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
	}


	

	function compressorModule ( schema_id, name, pos_x, pos_y) {
		this.schema_id = schema_id;
		this.name = name;
		this.pos_x = pos_x;
		this.pos_y = pos_y;
	}



	$scope.schema = [];

	$scope.initializeModuleList = function() {
		
		for ( i = 0; i < $scope.moduleNames.length; i++ ){
			//add 2 to i b/c 0 and 1 are reserved for input & output
			var liM = new liModule(i+2,$scope.moduleNames[i]);
			$scope.moduleList.push(liM);
		}
	};


	$scope.numNets;
	$scope.init = function() {
		$scope.initializeModuleList();
		$scope.numNets = 0;
		$scope.addModuleToSchema("Input",5,170);
		$scope.addModuleToSchema("Output",920,170);
		console.log("schema of length: " + $scope.schema.length);

		//handle connection bindings
		jsPlumb.bind("connection", function (info) {
			var sourceId = $(info.source).attr('schema-id');
			var targetId = $(info.target.parentNode.parentNode).attr('schema-id');

			console.log("connection was established, sid:"+sourceId+", tid:"+targetId);
			var cur_net_id = $scope.mr_net_id++;
			console.log("target id is " + targetId);

			//input sound module net id = 0
			//output sound module net id = 1
			if (sourceId == -2) {
				cur_net_id = 0;
			} else if (targetId == -1){
				cur_net_id = 1;
			}

			//if source already has an output net, use the same id
			var sourceModule = getSchemaModule(sourceId);
			var targetModule = getSchemaModule(targetId);
			console.log("sourceModule schema_id = " + sourceModule.schema_id);
			console.log("targetModule schema_id = " + targetModule.schema_id);
			
			if (sourceModule.outputNets.length > 0 ) {
				var output_net_id = sourceModule.outputNets[0];
				console.log("source's output net id is " + output_net_id);
				cur_net_id = output_net_id;
				$scope.numNets--;//increments at the end of function anyways
				$scope.mr_net_id--;
			}


			//assign input net to appropriate schema module
			
			sourceModule.outputNets.push(cur_net_id);
			targetModule.inputNets.push(cur_net_id);
			/*
			for ( i = 0; i < $scope.schema.length; i++ ){
				if ( $scope.schema[i].schema_id == sourceId ) {
					console.log("pushed onto schema id: "+$scope.schema[i].schema_id+"outputNets net id: " + cur_net_id);
					$scope.schema[i].outputNets.push(cur_net_id);
				}
				if ( $scope.schema[i].schema_id == targetId ) {
					console.log("pushed onto schema id: "+$scope.schema[i].schema_id+"inputNets net id: " + cur_net_id);
					$scope.schema[i].inputNets.push(cur_net_id);
				}
			}*/
			$scope.numNets++;
		}); 
	};

	//droppable callback function
	//delegates which snd-mdl object to place in the schema
	$scope.addModuleToSchema = function(type_name, pos_x, pos_y) {
		console.log("module name: " + type_name + ", x: " + pos_x + ", y: " + pos_y);
		//Create appropriate object based on module type
		var soundModule;
		switch( type_name ){
			case 'Input':
				soundModule = inputModule;
				break;
			case 'Output':
				soundModule = outputModule;
				break;
			case 'Delay':
				soundModule = delayModule;
				break;
			case 'Gain':
				soundModule = gainModule;
				break;
			case 'Summer':
				soundModule = summerModule;
				break;
			case 'Envelope Follower':
				soundModule = envelopeFollowerModule;
				break;
			case 'Filter':
				soundModule = filterModule;
				break;
			default:
				throw "Unsupported soundModule: " + type_name;
		}
		//Add to the schema
		$scope.schema.push( new soundModule(++$scope.mr_schema_uid,type_name,pos_x,pos_y));
	}

	function getSchemaModule(s_id){
		console.log("getSchemaModule("+s_id+")");
		for (var i=0; i<$scope.schema.length; i++){
			if ($scope.schema[i].schema_id == s_id) {
				console.log("schema_id is " + s_id);
				return $scope.schema[i];
			}
		}
		return -1;
	}


	$scope.knobs = [];
	$scope.knobs[0] = -1;
	$scope.knobs[1] = -1;
	$scope.knobs[2] = -1;
	$scope.knobs[3] = -1;
	$scope.logSchema = function(){
		console.log("Logging schema");

		//Determine if sound modules are controlled by knobs
		for( var i=0; i< $scope.knobs.length; i++){
			var curKnob = $scope.knobs[i];
			console.log("knob"+i+" value: " + curKnob);
			if (curKnob != -1) {
				for (var s = 2; s < $scope.schema.length; s++ ){
					if ($scope.schema[s].schema_id == curKnob) {
						$scope.schema[s].paramType = 2;
						$scope.schema[s].val = i; //knob id
					}
				}
			}
		}
		

		var numModules = [];
		numModules[0] = 0;
		var numNets = [];
		numNets[0] = $scope.numNets;
		var typeIdentifiers = [];
		var inputNets = [];
		var outputNets = [];
		var numArgs = 0;
		var argVals = [];
		var paramTypes = [];
		var paramVals = [];
		for( i = 2; i < $scope.schema.length; i++ ){
			numModules[0]++;
			var curBlock = $scope.schema[i];
			typeIdentifiers.push(curBlock.type_id);
			inputNets.push(curBlock.inputNets[0]);
			outputNets.push(curBlock.outputNets[0]);
			numArgs += curBlock.numArgs;
			//get appropriate arg vals
			if (curBlock.name == "Delay") {
				argVals.push(curBlock.minVal);
				argVals.push(curBlock.maxVal);
			} else if(curBlock.name == "Gain"){
				argVals.push(curBlock.maxVal);
				if (curBlock.gainType == "Linear") {
					argVals.push(0);
				} else {
					argVals.push(1);
				}
			} else if ($scope.schema[i].name == "Summer") {
				argVals.push(curBlock.inputNets[1]);
			}

			paramTypes.push(curBlock.paramType);
			
			paramVals.push(curBlock.val);
			
		}

		//get net ids from serialize.js

		var concatList = numModules.concat(typeIdentifiers).concat(numNets).concat(inputNets).concat(outputNets).concat(numArgs).concat(argVals).concat(paramTypes).concat(paramVals);
		var listLength = [];
		listLength[0] = concatList.length + 1;
		var serializedList = listLength.concat(concatList);
		var serializedString = "";
		for( i = 0; i< serializedList.length; i++ ){
			serializedString+= serializedList[i] + " ";
		}
		$("#serial-textarea").html(serializedString);
		sendToArduino(serializedString);
	}

	$scope.clearSchema = function(){
		$scope.mr_schema_uid = -3; //<-- most recent unique identifier for each module on canvas
		$scope.mr_net_id = 1; //<-- most recently used unique net id
		$scope.schema = [];
		$scope.addModuleToSchema("Input",5,170);
		$scope.addModuleToSchema("Output",920,170);
		jsPlumb.detachEveryConnection();
	}

});

/*
	CUSTOM DIRECTIVES:
		li-module: draggable menu item sound modules
		canvas: droppable canvas that holds the schema
				--is responsible for converting li-modules into block-modules

*/


/*
	Make all liModules draggable onto canvas
*/
app.directive('liModule', function() {
	return {
		link: function(scope, element, attrs){
			console.log("making liModule draggable");
			element.draggable({
				helper: "clone"
			});
		}
	}
});

/*
	Enable canvas to accept draggable liModules and 
	Calls addModuleToSchema on accepted liModule
*/

app.directive('dropCanvas',function() {
	return {
		link: function(scope, element, attrs){
			console.log("Make this element droppable");
			element.droppable({
				drop:function (event, ui ) {
					console.log("inside drop call back");
					
					var dragEl = angular.element(ui.draggable);
					if (dragEl.hasClass('module')){
						var pos = ui.helper.position();
						var trueLeft = pos.left + angular.element(this).width();
						var moduleName = angular.element(ui.draggable).data('identifier');
						
						scope.addModuleToSchema(moduleName, trueLeft, pos.top);
						scope.$apply();
					}
				}
			});
			
		}
	}
});

/* All the HTML attributes belonging to this directive are 
   reflected onto the generated template. Template gets binded
   to appropriate scope.schema block
*/
app.directive('soundModule', function($http, $templateCache, $compile, $parse) {
	console.log("soundModule directive");

	return {
		replace: true,
		controller: 'PlumbCtrl',
		// templateUrl: "../html/templates/Gain.html",
    	link: function ( scope, element, attrs ) {
    		scope.$watch(attrs.moduleType, function() {
    			console.log("module type changed to " + attrs.moduleType);

       var templateName = $parse(attrs.moduleType)(scope);
    		$http.get('../html/templates/' + attrs.moduleType + '.html', {cache: $templateCache}).success(function (tplContent) {
    			element.html($compile(tplContent)(scope));
    			//$compile(tplContent)(scope); 
    			jsPlumb.draggable(element, {
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
    		jsPlumb.makeSource(element.find(".outputCol"), {
				parent: element,
				anchor: 'Continuous'
    		});
    		 jsPlumb.makeTarget(element.find(".inputCol"), {
    		 	anchor: 'Continuous'
    		 });

    		 
    		});
    		});

    	}

	};
});








