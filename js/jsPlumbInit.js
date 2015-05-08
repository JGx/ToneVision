jsPlumb.ready(function() {
	console.log("jsplumb is ready");
	var instance = jsPlumb.getInstance({
		// default drag options
		DragOptions : { cursor: 'pointer', zIndex:2000 },
		// the overlays to decorate each connection with.  note that the label overlay uses a function to generate the label text; in this
		// case it returns the 'labelText' member that we set on each connection in the 'init' method below.
		ConnectionOverlays : [
			[ "Arrow", { location:1 } ],
			[ "Label", { 
				location:0.1,
				id:"label",
				cssClass:"aLabel"
			}]
		],
		Container:"flowchart-demo"
	});

	// this is the paint style for the connecting lines..
	var connectorPaintStyle = {
		lineWidth:4,
		strokeStyle:"#61B7CF",
		joinstyle:"round",
		outlineColor:"white",
		outlineWidth:2
	},
	// .. and this is the hover style. 
	connectorHoverStyle = {
		lineWidth:4,
		strokeStyle:"#216477",
		outlineWidth:2,
		outlineColor:"white"
	},
	endpointHoverStyle = {
		fillStyle:"#216477",
		strokeStyle:"#216477"
	},
	// the definition of source endpoints (the small blue ones)
	sourceEndpoint = {
		endpoint:"Dot",
		paintStyle:{ 
			strokeStyle:"#7AB02C",
			fillStyle:"transparent",
			radius:7,
			lineWidth:3 
		},				
		isSource:true,
		connector:[ "Flowchart", { stub:[40, 60], gap:10, cornerRadius:5, alwaysRespectStubs:true } ],								                
		connectorStyle:connectorPaintStyle,
		hoverPaintStyle:endpointHoverStyle,
		connectorHoverStyle:connectorHoverStyle,
        dragOptions:{},
        overlays:[
        	[ "Label", { 
            	location:[0.5, 1.5], 
            	label:"Drag",
            	cssClass:"endpointSourceLabel" 
            } ]
        ]
	},		
	// the definition of target endpoints (will appear when the user drags a connection) 
	targetEndpoint = {
		endpoint:"Dot",					
		paintStyle:{ fillStyle:"#7AB02C",radius:11 },
		hoverPaintStyle:endpointHoverStyle,
		maxConnections:-1,
		dropOptions:{ hoverClass:"hover", activeClass:"active" },
		isTarget:true,			
        overlays:[
        	[ "Label", { location:[0.5, -0.5], label:"Drop", cssClass:"endpointTargetLabel" } ]
        ]
	}
});